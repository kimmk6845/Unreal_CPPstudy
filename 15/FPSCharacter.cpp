#include "FPSCharacter.h"

AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;	// 케릭터 기본 속도
	PlayerHP = 100.0f;
	PlayerStamina = 100.0f;
	availableSprint = true;
	ammo = 30;
	BaseDamage = 20.0f;
	reach = 250.0f;
	Adrenaline = false;
	AdTime = 120.0f;	// 아드레날린 버프시간 2분
	
	// 카메라 컴포넌트 생성
	CHelpers::CreateComponent<UCameraComponent>(this, &camera, "camera", GetCapsuleComponent());
	camera->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f + BaseEyeHeight));
	camera->bUsePawnControlRotation = true;

	// 1인칭 케릭터 컴포넌트 생성 + 메시, 애니메이션
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh1p, "Mesh1p", camera);
	Mesh1p->SetOnlyOwnerSee(true);
	Mesh1p->bCastDynamicShadow = false;
	Mesh1p->CastShadow = false;
	Mesh1p->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));		// Y, Z, X
	Mesh1p->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	USkeletalMesh* mesh1;
	CHelpers::GetAsset<USkeletalMesh>(&mesh1, "SkeletalMesh'/Game/FirstPerson/Character/Mesh/SK_Mannequin_Arms'");
	Mesh1p->SetSkeletalMesh(mesh1);
	TSubclassOf<UAnimInstance> anim1;
	CHelpers::GetClass<UAnimInstance>(&anim1, "AnimBlueprint'/Game/FirstPerson/Animations/FirstPerson_AnimBP'");
	Mesh1p->SetAnimInstanceClass(anim1);

	// 1인칭 총 컴포넌트 생성
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &FPSGun, "FPSGun", RootComponent);
	FPSGun->SetOnlyOwnerSee(true);
	FPSGun->bCastDynamicShadow = false;
	FPSGun->CastShadow = false;
	USkeletalMesh* gun;
	CHelpers::GetAsset<USkeletalMesh>(&gun, "SkeletalMesh'/Game/FirstPerson/FPWeapon/Mesh/SK_FPGun'");
	FPSGun->SetSkeletalMesh(gun);

	// 3인칭 케릭터 메시 씌우기, 애니메이션
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/_My/Asset/Swat/Swat'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetOwnerNoSee(true);
	TSubclassOf<UAnimInstance> anim;
	CHelpers::GetClass<UAnimInstance>(&anim, "AnimBlueprint'/Game/_My/Asset/Swat/Anim/Swat_Anim'");
	GetMesh()->SetAnimInstanceClass(anim);

	// 사운드
	CHelpers::GetAsset<USoundBase>(&FireSound, "SoundWave'/Game/FirstPerson/Audio/FirstPersonTemplateWeaponFire02'");
	CHelpers::GetAsset<USoundBase>(&EmptyAmmo, "SoundWave'/Game/_My/Audio/OutOfAmmo'");
	CHelpers::GetAsset<USoundBase>(&ReloadSound, "SoundWave'/Game/_My/Audio/reload'");

	// 파티클
	CHelpers::GetAsset<UParticleSystem>(&ShotEffect, "ParticleSystem'/Game/_My/particle/P_Shoot'");
	CHelpers::GetAsset<UParticleSystem>(&ZombieHitEffect, "ParticleSystem'/Game/_My/particle/P_Blood'");
	CHelpers::GetAsset<UParticleSystem>(&HitEffect, "ParticleSystem'/Game/_My/particle/P_BulletImpact'");
	CHelpers::GetAsset<UParticleSystem>(&HeadShotEffect, "ParticleSystem'/Game/_My/particle/P_Head'");
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FName GunSocketName = TEXT("GripPoint");
	FPSGun->AttachToComponent(Mesh1p, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), GunSocketName);

	// 인벤토리 설정
	Inventory.SetNum(4);
	currentInteractable = nullptr;

	if (GetWorld())
	{
		gamemode = Cast<ACGameModeBase>(GetWorld()->GetAuthGameMode());
		if (gamemode)
		{
			PlayerWidget = gamemode->GetPlayerWidget();
			if (PlayerWidget)
			{
				PlayerWidget->SetHP(GetPlayerHP());
				PlayerWidget->SetHPBar(GetPlayerHP());
				PlayerWidget->SetRemainAmmo(GetAmmo());
				PlayerWidget->SetStamina(GetPlayerStamina());
			}
		}

		if (IsValid(BloodEffectClass))	// 데미지 받았을 때 화면 붉어지는 위젯
		{
			BloodEffectWidget = Cast<UDamageRecieveWidget>(CreateWidget(GetWorld(), BloodEffectClass));
		}
	}
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckForInteractables();

	PlayerWidget->SetHP(GetPlayerHP());
	PlayerWidget->SetHPBar(GetPlayerHP());
	PlayerWidget->SetRemainAmmo(GetAmmo());
	PlayerWidget->SetStamina(GetPlayerStamina());

	if (GetCharacterMovement()->MaxWalkSpeed > 400.0f && GetVelocity().X != 0 && GetVelocity().Y != 0)	// 스프린트 중이면 스테미너 감소
	{
		PlayerStamina -= DeltaTime * 10.0f;

		if (PlayerStamina < 0)	// 스테미너를 모두 소진하면 당분간 스프린트를 사용 못 함
		{
			availableSprint = false;
			GetCharacterMovement()->MaxWalkSpeed = 400.0f;
		}
	}
	else
	{
		// 스테미너가 100까지 서서히 증가
		if (PlayerStamina <= 100.0f)
		{
			PlayerStamina += DeltaTime * 5.0f;

			if (PlayerStamina > 30.0f)	// 30 이상이 되어야 스프린트가 가능하기 때문에 플레이어가 스테미너를 조절해가며 사용해야 함
				availableSprint = true;
		}
	}

	if (Adrenaline)	// 아드레날린 사용 시
	{
		AdTime -= DeltaTime * 1.0f;

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Remain Adrenaline Time: %f"), AdTime));

		if (AdTime < 0)
		{
			AdrenalineBuffOff();	// 위젯 제거
			BaseDamage -= 10.0f;		//  기본 데미지로 복귀
			GLog->Log(FString("Apply Base Damage"));
			Adrenaline = false;
			AdTime = 120.0f;
		}
	}
}

// 데미지 받는 함수
float AFPSCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float GetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (PlayerHP > 0)
	{
		PlayerHP -= GetDamage;
		PlayerWidget->SetHP(GetPlayerHP());
		PlayerWidget->SetHPBar(GetPlayerHP());

		if (BloodEffectWidget != nullptr)
		{
			BloodEffectWidget->AddToViewport();
		}

	}

	return 0.0f;
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// 축 매핑 바인딩
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::OnMoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::OnLookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::OnTurn);

	// 액션 매핑 바인딩
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPSCharacter::OnRunning);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPSCharacter::OffRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacter::OffFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFPSCharacter::Reloading);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFPSCharacter::Interact);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AFPSCharacter::ToggleInventory);

}


// 축 매핑 *****************
void AFPSCharacter::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void AFPSCharacter::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void AFPSCharacter::OnLookUp(float Axis)
{
	AddControllerPitchInput(Axis);
}

void AFPSCharacter::OnTurn(float Axis)
{
	AddControllerYawInput(Axis);
}
// *************************

// 액션 매핑*****************
void AFPSCharacter::OnRunning()
{
	if(availableSprint)
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	else
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void AFPSCharacter::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void AFPSCharacter::OnFire()
{
	isFiring = true;
	Fire();
}

void AFPSCharacter::OffFire()
{
	isFiring = false;
}

void AFPSCharacter::Reloading()
{
	if (ammo != 30)
	{
		IsReloading = true;
		ammo = 30;
		if (ReloadSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
		}

		// 재장전 3초 딜레이
		FTimerHandle WaitHandle;
		float WaitTime = 3.0f;
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				IsReloading = false;
				PlayerWidget->SetRemainAmmo(GetAmmo());
			}), WaitTime, false);
	}
}

void AFPSCharacter::ToggleInventory()
{
	if (gamemode)
	{
		APlayerController* controller = GetWorld()->GetFirstPlayerController();
		if (IsValid(invenClass))
		{
			if (toggleinven == false)
			{
				InventoryWidget = Cast<UInventoryWidget>(CreateWidget(GetWorld(), invenClass));
				if (InventoryWidget != nullptr)
				{
					controller->bShowMouseCursor = true;
					controller->bEnableClickEvents = true;
					toggleinven = true;

					InventoryWidget->AddToViewport();
				}
			}
			else
			{
				controller->bShowMouseCursor = false;
				controller->bEnableClickEvents = false;
				toggleinven = false;
				InventoryWidget->RemoveFromViewport();
			}
		}
	}
}

void AFPSCharacter::Interact()
{
	if (currentInteractable != nullptr)
	{
		currentInteractable->Interact_Implementation();
	}
}
// *************************

// 사격
void AFPSCharacter::Fire()
{
	if (ammo > 0 && IsReloading == false)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			if (isFiring)
			{
				FHitResult OutHit;
				FVector Start = FPSGun->GetComponentLocation();
				FVector ForwardVector = camera->GetForwardVector();
				FVector End = (ForwardVector * 5000.0f) + Start;

				FCollisionQueryParams CollisionParams;
				CollisionParams.AddIgnoredActor(this);
				bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
				if (isHit)
				{
					if (OutHit.bBlockingHit)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("Hit Actor: %s"), *OutHit.GetActor()->GetName()));
						//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
						//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Impact Normal: %s"), *OutHit.ImpactNormal.ToString()));

						AActor* HitActor = OutHit.GetActor();
						float HitDamage = BaseDamage + FMath::RandRange(0.0f, 10.0f);
						if (OutHit.BoneName == "Head")	// 헤드샷 3배	(보스와 male2는 헤드샷 적용 x)
						{
							UE_LOG(LogTemp, Warning, TEXT("critical damage : %f, BoneName : %s"), HitDamage * 3, *OutHit.BoneName.ToString());
							UGameplayStatics::ApplyPointDamage(HitActor, HitDamage * 3, HitActor->GetActorLocation(), OutHit, nullptr, this, nullptr);
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HeadShotEffect, (OutHit.ImpactPoint));
						}
						else if (OutHit.BoneName == "Spine2")	// 상반신 2배
						{
							UE_LOG(LogTemp, Warning, TEXT("damage : %f, BoneName : %s"), HitDamage * 2, *OutHit.BoneName.ToString());
							UGameplayStatics::ApplyPointDamage(HitActor, HitDamage * 2, HitActor->GetActorLocation(), OutHit, nullptr, this, nullptr);
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HeadShotEffect, (OutHit.ImpactPoint));
						}
						else
							UGameplayStatics::ApplyPointDamage(HitActor, HitDamage, HitActor->GetActorLocation(), OutHit, nullptr, this, nullptr);

						if(HitActor->ActorHasTag("Zombie"))
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ZombieHitEffect, (OutHit.ImpactPoint));

					}
					UGameplayStatics::SpawnEmitterAttached(ShotEffect, FPSGun, TEXT("Shoot"));
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, (OutHit.ImpactPoint));				// 물체 hit
				}
				
				// 반동
				AddControllerYawInput(FMath::RandRange(-0.15f, 0.15f));
				AddControllerPitchInput(FMath::RandRange(-0.5f, -0.3f));

				GetWorld()->GetTimerManager().SetTimer(timer, this, &AFPSCharacter::Fire, 0.12f, false);
				ammo--;
				PlayerWidget->SetRemainAmmo(GetAmmo());

				// 사운드
				if (FireSound != NULL)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
				}
				// 애니메이션
				if (FireAnimation != NULL)
				{
					UAnimInstance* AnimInstance = Mesh1p->GetAnimInstance();
					if (AnimInstance != NULL)
					{
						AnimInstance->Montage_Play(FireAnimation, 1.f);
					}
				}
			}
		}
	}
	else if(ammo == 0)
	{
		// 빈 탄창 소리
		if (EmptyAmmo != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, EmptyAmmo, GetActorLocation());
		}
	}

}

void AFPSCharacter::CheckForInteractables()
{
	FVector StartTrace = camera->GetComponentLocation();
	FVector EndTrace = (camera->GetForwardVector() * reach) + StartTrace;

	FHitResult HitResult;
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_WorldDynamic, CQP);

	AInteractable* interactable = Cast<AInteractable>(HitResult.GetActor());
	if (interactable == NULL)
	{
		helpText = FString("");
		currentInteractable = nullptr;
		PlayerWidget->SetHelpText(helpText);
		return;
	}
	else
	{
		currentInteractable = interactable;
		helpText = interactable->interactableHelpText;
		PlayerWidget->SetHelpText(helpText);
	}
}

bool AFPSCharacter::AddItemToInventory(APickupItemBase* item)
{
	if (item != NULL)
	{
		const int32 AvailableSlot = Inventory.Find(nullptr);

		if (AvailableSlot != INDEX_NONE)
		{
			Inventory[AvailableSlot] = item;
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You can't carry any more item"));
			return false;
		}
	}
	else return false;
}

UTexture2D* AFPSCharacter::GetTumbnailAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot] != NULL)
	{
		return Inventory[Slot]->pickupThumbnail;
	}
	else return nullptr;
}

FString AFPSCharacter::GetItemNameAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot] != NULL)
	{
		return Inventory[Slot]->itemName;
	}
	return FString("None");
}

void AFPSCharacter::UseItemAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot] != NULL)
	{
		Inventory[Slot]->Use_Implementation();
		Inventory[Slot] = NULL;
	}
}

// 아드레날린 위젯
void AFPSCharacter::AdrenalineBuffOn()
{
	if (gamemode)
	{
		if (IsValid(BuffClass))
		{
			AdrenalineWidget = Cast<UAdrenalineBuffWidget>(CreateWidget(GetWorld(), BuffClass));
			if (AdrenalineWidget != nullptr)
			{
				AdrenalineWidget->AddToViewport();
			}
		}
	}
}

void AFPSCharacter::AdrenalineBuffOff()
{
	if (AdrenalineWidget != nullptr)
	{
		AdrenalineWidget->RemoveFromViewport();
	}
}
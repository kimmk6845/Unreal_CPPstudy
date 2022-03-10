#include "FPSCharacter.h"

AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;	// �ɸ��� �⺻ �ӵ�
	PlayerHP = 100.0f;
	PlayerStamina = 100.0f;
	availableSprint = true;
	ammo = 30;
	BaseDamage = 20.0f;
	reach = 250.0f;
	Adrenaline = false;
	AdTime = 120.0f;	// �Ƶ巹���� �����ð� 2��
	
	// ī�޶� ������Ʈ ����
	CHelpers::CreateComponent<UCameraComponent>(this, &camera, "camera", GetCapsuleComponent());
	camera->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f + BaseEyeHeight));
	camera->bUsePawnControlRotation = true;

	// 1��Ī �ɸ��� ������Ʈ ���� + �޽�, �ִϸ��̼�
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

	// 1��Ī �� ������Ʈ ����
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &FPSGun, "FPSGun", RootComponent);
	FPSGun->SetOnlyOwnerSee(true);
	FPSGun->bCastDynamicShadow = false;
	FPSGun->CastShadow = false;
	USkeletalMesh* gun;
	CHelpers::GetAsset<USkeletalMesh>(&gun, "SkeletalMesh'/Game/FirstPerson/FPWeapon/Mesh/SK_FPGun'");
	FPSGun->SetSkeletalMesh(gun);

	// 3��Ī �ɸ��� �޽� �����, �ִϸ��̼�
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/_My/Asset/Swat/Swat'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetOwnerNoSee(true);
	TSubclassOf<UAnimInstance> anim;
	CHelpers::GetClass<UAnimInstance>(&anim, "AnimBlueprint'/Game/_My/Asset/Swat/Anim/Swat_Anim'");
	GetMesh()->SetAnimInstanceClass(anim);

	// ����
	CHelpers::GetAsset<USoundBase>(&FireSound, "SoundWave'/Game/FirstPerson/Audio/FirstPersonTemplateWeaponFire02'");
	CHelpers::GetAsset<USoundBase>(&EmptyAmmo, "SoundWave'/Game/_My/Audio/OutOfAmmo'");
	CHelpers::GetAsset<USoundBase>(&ReloadSound, "SoundWave'/Game/_My/Audio/reload'");

	// ��ƼŬ
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

	// �κ��丮 ����
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

		if (IsValid(BloodEffectClass))	// ������ �޾��� �� ȭ�� �Ӿ����� ����
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

	if (GetCharacterMovement()->MaxWalkSpeed > 400.0f && GetVelocity().X != 0 && GetVelocity().Y != 0)	// ������Ʈ ���̸� ���׹̳� ����
	{
		PlayerStamina -= DeltaTime * 10.0f;

		if (PlayerStamina < 0)	// ���׹̳ʸ� ��� �����ϸ� ��а� ������Ʈ�� ��� �� ��
		{
			availableSprint = false;
			GetCharacterMovement()->MaxWalkSpeed = 400.0f;
		}
	}
	else
	{
		// ���׹̳ʰ� 100���� ������ ����
		if (PlayerStamina <= 100.0f)
		{
			PlayerStamina += DeltaTime * 5.0f;

			if (PlayerStamina > 30.0f)	// 30 �̻��� �Ǿ�� ������Ʈ�� �����ϱ� ������ �÷��̾ ���׹̳ʸ� �����ذ��� ����ؾ� ��
				availableSprint = true;
		}
	}

	if (Adrenaline)	// �Ƶ巹���� ��� ��
	{
		AdTime -= DeltaTime * 1.0f;

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Remain Adrenaline Time: %f"), AdTime));

		if (AdTime < 0)
		{
			AdrenalineBuffOff();	// ���� ����
			BaseDamage -= 10.0f;		//  �⺻ �������� ����
			GLog->Log(FString("Apply Base Damage"));
			Adrenaline = false;
			AdTime = 120.0f;
		}
	}
}

// ������ �޴� �Լ�
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
	
	// �� ���� ���ε�
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::OnMoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::OnLookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::OnTurn);

	// �׼� ���� ���ε�
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPSCharacter::OnRunning);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPSCharacter::OffRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacter::OffFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFPSCharacter::Reloading);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFPSCharacter::Interact);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AFPSCharacter::ToggleInventory);

}


// �� ���� *****************
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

// �׼� ����*****************
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

		// ������ 3�� ������
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

// ���
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
						if (OutHit.BoneName == "Head")	// ��弦 3��	(������ male2�� ��弦 ���� x)
						{
							UE_LOG(LogTemp, Warning, TEXT("critical damage : %f, BoneName : %s"), HitDamage * 3, *OutHit.BoneName.ToString());
							UGameplayStatics::ApplyPointDamage(HitActor, HitDamage * 3, HitActor->GetActorLocation(), OutHit, nullptr, this, nullptr);
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HeadShotEffect, (OutHit.ImpactPoint));
						}
						else if (OutHit.BoneName == "Spine2")	// ��ݽ� 2��
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
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, (OutHit.ImpactPoint));				// ��ü hit
				}
				
				// �ݵ�
				AddControllerYawInput(FMath::RandRange(-0.15f, 0.15f));
				AddControllerPitchInput(FMath::RandRange(-0.5f, -0.3f));

				GetWorld()->GetTimerManager().SetTimer(timer, this, &AFPSCharacter::Fire, 0.12f, false);
				ammo--;
				PlayerWidget->SetRemainAmmo(GetAmmo());

				// ����
				if (FireSound != NULL)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
				}
				// �ִϸ��̼�
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
		// �� źâ �Ҹ�
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

// �Ƶ巹���� ����
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
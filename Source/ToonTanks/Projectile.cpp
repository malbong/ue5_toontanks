// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;

	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projecilte Trail Particle"));
	TrailParticle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	UGameplayStatics::PlaySoundAtLocation(this, ProjectileSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent *HitComponent,
						AActor *OtherActor,
						UPrimitiveComponent *OtherComp,
						FVector NormalImpulse,
						const FHitResult &HitResult)
{
	if (OtherActor == nullptr || OtherActor == this || OtherActor == GetInstigator() || OtherActor == GetOwner())
		return;

	AController *InstigatorController = GetInstigatorController();

	UGameplayStatics::ApplyDamage(OtherActor,
								  Damage, InstigatorController, this, UDamageType::StaticClass());

	UGameplayStatics::PlaySoundAtLocation(this, ProjectileSound, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), GetActorRotation());

	Destroy();
}

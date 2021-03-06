// == LOCAL

// .. IMPORTS

#include "FpsCube.h"
#include "FpsCharacter.h"
#include "FpsGameMode.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsCube::AFpsCube(
    )
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/CubeStaticMesh.CubeStaticMesh'" ) );

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
    StaticMeshComponent->SetStaticMesh( StaticMesh );
    StaticMeshComponent->SetSimulatePhysics( true );
    StaticMeshComponent->SetCollisionProfileName( TEXT( "Pawn" ) );

    RootComponent = StaticMeshComponent;

    ActivationBoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "ActivationBox" ) );
    ActivationBoxComponent->bGenerateOverlapEvents = true;
    ActivationBoxComponent->OnComponentBeginOverlap.AddDynamic( this, &AFpsCube::OnActivationBoxComponentBeginOverlap );
    ActivationBoxComponent->SetupAttachment( RootComponent );

    SetActorEnableCollision( true );

    Reset();
}

// -- EVENTS

void AFpsCube::OnActivationBoxComponentBeginOverlap(
    class UPrimitiveComponent * primitive_component,
    class AActor * other_actor,
    class UPrimitiveComponent * other_primitive_component,
    int32 other_body_index,
    bool from_sweep,
    const FHitResult & hit_result
    )
{
    if ( State == EState_Free
         && other_actor->IsA( AFpsCharacter::StaticClass() ) )
    {
        AFpsGameMode::Character->HoldItem( this );
    }
}

// -- OPERATIONS

void AFpsCube::Reset(
    )
{
    ActivationBoxComponent->SetRelativeLocation( FVector( 0, 0, 0 ) );
    ActivationBoxComponent->SetRelativeScale3D( FVector( 2, 2, 2 ) );

    State = EState_Free;
}

// ~~

void AFpsCube::BeginPlay(
    )
{
    Super::BeginPlay();

    Reset();
}

// ~~

void AFpsCube::Tick(
    float elapsed_time
    )
{
    Super::Tick( elapsed_time );
}

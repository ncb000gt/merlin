#include "merlin.h"

namespace merlin {

Merlin::Merlin() {
    // MagickWandGenesis();
}

Merlin::~Merlin() {
    MagickWandTerminus();
}

void
Merlin::Initialize(Handle<Object> target) {
    HandleScope scope;

    Handle<Object> merlin = Object::New();
    merlin->Set(String::NewSymbol("version"),
                String::New(MERLIN_VERSION));

    MerlinImage::Initialize(merlin);

    MagickWandGenesis();
    
    target->Set(String::NewSymbol("merlin"), merlin);
}

} // namespace

extern "C" void
init(Handle<Object> target)
{
    HandleScope scope;

    merlin::Merlin::Initialize(target);
}

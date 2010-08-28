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

    target->Set(String::NewSymbol("version"),
                String::New(MERLIN_VERSION));

    MerlinImage::Initialize(target);

    MagickWandGenesis();
    
    Handle<ObjectTemplate> global = ObjectTemplate::New();
    Handle<Context> context = Context::New(NULL, global);
    Context::Scope context_scope(context);

    context->Global()->Set(String::NewSymbol("merlin"), target);
}

} // namespace

extern "C" void
init(Handle<Object> target)
{
    HandleScope scope;

    merlin::Merlin::Initialize(target);
}

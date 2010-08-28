#include <merlin.h>

namespace merlin {

void
Merlin::Initialize(Handle<Object> target) {
    HandleScope scope;

    Handle<ObjectTemplate> merlin = ObjectTemplate::New();
    merlin->Set(String::NewSymbol("version"),
                String::New(MERLIN_VERSION));

    MagickWandGenesis();
    
    target->Set(String::NewSymbol("merlin"), merlin->NewInstance());
}

} // namespace

extern "C" void
init(Handle<Object> target)
{
    HandleScope scope;

    merlin::Merlin::Initialize(target);
}


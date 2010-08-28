#ifndef SRC_MERLIN_H_
#define SRC_MERLIN_H_

#include <cstdlib>
#include <node.h>
#include <node_buffer.h>

#include <cassert>  // for assert()

#define MERLIN_VERSION "v0.0.1"

#define BAD_ARGUMENTS Exception::TypeError(String::New("Bad argument"))

using namespace v8;
using namespace node;

namespace merlin {

// Ensure that merlin is properly initialised:
class Merlin {
  public:
    static Persistent<FunctionTemplate> constructor_template;

    static void Initialize(Handle<Object>);

    Merlin();
    virtual ~Merlin();

  private:

    static Merlin init_;
};

} // namespace Merlin

#endif SRC_MERLIN_H_


namespace merlin {

void
Merlin::Initialize(Handle<Object> target) {
    HandleScope scope;

    Handle<ObjectTemplate> merlin = ObjectTemplate::New();
    merlin->Set(String::NewSymbol("version"),
                String::New(MERLIN_VERSION));
    
    target->Set(String::NewSymbol("merlin"), merlin->NewInstance());
}

} // namespace

extern "C" void
init(Handle<Object> target)
{
    HandleScope scope;

    merlin::Merlin::Initialize(target);
}


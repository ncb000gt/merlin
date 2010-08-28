#ifndef SRC_MERLIN_IMAGE_H_
#define SRC_MERLIN_IMAGE_H_

#include <cstdlib>
#include <node.h>
#include <node_buffer.h>
#include <wand/MagickWand.h>

#include <merlin.h>

using namespace v8;

namespace merlin {

class MerlinImage : public node::ObjectWrap {
  public:
      static Persistent<FunctionTemplate> constructor_template;
      static void Initialize(Handle<Object>);
      static Handle<Value> New(const Arguments&);

      MerlinImage(node::Buffer* buffer);
      virtual ~MerlinImage();

  private:
      node::Buffer *buffer;
      MagickWand* wand;
};

} // namespace Merlin

#endif SRC_MERLIN_IMAGE_H_

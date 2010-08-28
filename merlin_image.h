#ifndef SRC_MERLIN_IMAGE_H_
#define SRC_MERLIN_IMAGE_H_

#include <cstdlib>
#include <node.h>
#include <node_buffer.h>
#include <wand/MagickWand.h>

#include <merlin.h>

namespace merlin {

class MerlinImage : public node::ObjectWrap {
  public:
      static Persistent<v8::FunctionTemplate> constructor_template;
      static void Initialize(v8::Handle<Object>);
      static Handle<v8::Value> New(const v8::Arguments&);

      MerlinImage();
      virtual ~MerlinImage();
};

} // namespace Merlin

#endif SRC_MERLIN_IMAGE_H_

//Taken from https://github.com/pkrumins/node-png/blob/791d4c6df1402daa15dc7930f084d95c48e63c98/src/buffer_compat.h
#ifndef buffer_compat_h
#define buffer_compat_h

#include <node.h>
#include <node_buffer.h>
#include <v8.h>

char *BufferData(node::Buffer *b);
size_t BufferLength(node::Buffer *b);

char *BufferData(v8::Local<v8::Object> buf_obj);
size_t BufferLength(v8::Local<v8::Object> buf_obj);


#endif  // buffer_compat_h

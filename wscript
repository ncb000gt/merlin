import Options
from os import unlink, symlink, popen
from os.path import exists 
import subprocess

srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.target = "merlin"
  obj.source = "merlin.cpp merlin_image.cpp"
  imflags = subprocess.Popen(['Magick-config', '--cppflags'], stdout = subprocess.PIPE).stdout.read()
  obj.cxxflags = ["-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE", "-I/opt/local/include/ImageMagick", "-I../"] + (' ').split(imflags)[:-1]

def shutdown():
  if Options.commands['clean']:
    if exists('merlin.node'): unlink('merlin.node')
  else:
    if exists('build/default/merlin.node') and not exists('merlin.node'):
      symlink('build/default/merlin.node', 'merlin.node')


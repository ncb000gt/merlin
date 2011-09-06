import Options, sys
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
  obj.source = "src/merlin.cpp src/merlin_image.cpp src/buffer_compat.cpp"

  imflags = "-I/usr/include/GraphicsMagick/"

  config_pre = 'Magick'
  if sys.platform == 'darwin':
    config_pre = 'GraphicsMagick' # seems that GM has this file on the mac.
    imflags = subprocess.Popen(['GraphicsMagick-config', '--cppflags'], stdout = subprocess.PIPE).stdout.read()


  ldflags = subprocess.Popen([config_pre + '-config', '--ldflags', '--libs'], stdout = subprocess.PIPE).stdout.read()

  wandflags = subprocess.Popen([config_pre + 'Wand-config', '--ldflags', '--libs'], stdout = subprocess.PIPE).stdout.read()

  obj.cxxflags = ["-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE", "-I../src"] + imflags.split() 

  obj.linkflags = ["-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE", "-I../src"] + imflags.split() + ldflags.split() + wandflags.split()

def shutdown():
  if Options.commands['clean']:
    if exists('merlin.node'): unlink('merlin.node')
  else:
    if exists('build/default/merlin.node') and not exists('merlin.node'):
      symlink('build/default/merlin.node', 'merlin.node')

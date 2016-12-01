
class BuildContext(object):
  
  def BuildSourceList(self, directory, sources):
    for i in range(len(sources)):
      sources[i] = directory + '/' + sources[i]
    return sources
    


context = BuildContext()

SConscript('src/SConscript', exports='context', variant_dir='build', duplicate=0)

SConscript('src/simplerenderer/SConscript', exports='context', variant_dir='build/simplerenderer', duplicate=0)

SConscript('tests/SConscript', exports='context', variant_dir='build/tests', duplicate=0)

project('Tried', 'c',
  default_options: ['warning_level=3', 'c_std=c2x']
)


cc = meson.get_compiler('c')




inc = include_directories('include')

project_dep = declare_dependency(
  include_directories: inc
)




raylib_dep = dependency('raylib',
  required: false,
  fallback: ['raylib', 'raylib_dep']
)

if not raylib_dep.found()
  error('couldn\'t find raylib dependency in the system, nor in the subprojects')
endif




math_dep = cc.find_library('m', required: true)




subdir('src')
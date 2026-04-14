project('Tried', 'c',
  default_options: ['warning_level=3', 'c_std=c2x']
)


inc = include_directories('include')

project_dep = declare_dependency(
  include_directories: inc
)


subdir('src')
project('YTChannel2RSSFeed','c')
PROJECT_NAME = meson.project_name()
LOCAL_DIR = meson.current_source_dir()

gtkdep = dependency('gtk4')

add_project_link_arguments('-pthread', language : 'c')

gnome = import('gnome')
resources = gnome.compile_resources('resources', 'YTChannel2RSSFeed.gresource.xml')

sourcefiles = files('src/main.c', 'src/algorithms.c', 'src/ip_lookup.c', 'src/callbacks.c')

executable(PROJECT_NAME, sourcefiles, resources, dependencies: gtkdep, c_args:[ '-DLOCAL_DIR="@0@/"'.format(LOCAL_DIR)], export_dynamic: true)

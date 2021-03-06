
################
# Dependencies #
################

gtd_deps = gnome_todo_deps + [
  plugins_dep,
]


################
# Header files #
################

enum_headers = files('gtd-enums.h')

headers = enum_headers + files(
  'engine/gtd-manager.h',
  'interfaces/gtd-activatable.h',
  'interfaces/gtd-panel.h',
  'interfaces/gtd-provider.h',
  'models/gtd-list-model-filter.h',
  'models/gtd-list-store.h',
  'notification/gtd-notification.h',
  'task-list-view/gtd-task-list-view.h',
  'gtd-clock.h',
  'gtd-object.h',
  'gtd-task.h',
  'gtd-task-list.h',
  'gtd-types.h',
  'gtd-utils.h',
  'gtd-window.h',
  'gnome-todo.h'
)

install_headers(headers, subdir: meson.project_name())


################
# Source files #
################

sources = files(
  'engine/gtd-manager.c',
  'engine/gtd-plugin-manager.c',
  'interfaces/gtd-activatable.c',
  'interfaces/gtd-panel.c',
  'interfaces/gtd-provider.c',
  'logging/gtd-log.c',
  'models/gtd-list-model-filter.c',
  'models/gtd-list-model-sort.c',
  'models/gtd-list-store.c',
  'models/gtd-task-model.c',
  'notification/gtd-notification.c',
  'notification/gtd-notification-widget.c',
  'provider/gtd-provider-popover.c',
  'provider/gtd-provider-row.c',
  'provider/gtd-provider-selector.c',
  'sidebar/gtd-sidebar.c',
  'sidebar/gtd-sidebar-list-row.c',
  'sidebar/gtd-sidebar-panel-row.c',
  'sidebar/gtd-sidebar-provider-row.c',
  'task-list-view/gtd-edit-pane.c',
  'task-list-view/gtd-dnd-row.c',
  'task-list-view/gtd-markdown-renderer.c',
  'task-list-view/gtd-new-task-row.c',
  'task-list-view/gtd-task-list-popover.c',
  'task-list-view/gtd-task-list-view.c',
  'task-list-view/gtd-task-row.c',
  'widgets/gtd-color-button.c',
  'widgets/gtd-empty-list-widget.c',
  'widgets/gtd-row-header.c',
  'gtd-application.c',
  'gtd-initial-setup-window.c',
  'gtd-clock.c',
  'gtd-object.c',
  'gtd-plugin-dialog.c',
  'gtd-plugin-dialog-row.c',
  'gtd-rows-common.c',
  'gtd-task.c',
  'gtd-task-list.c',
  'gtd-task-list-panel.c',
  'gtd-utils.c',
  'gtd-window.c',
  'main.c'
)


#############
# Resources #
#############

sources += gnome.compile_resources(
  'gtd-resources',
  'todo.gresource.xml',
  c_name: 'todo',
  export: true,
)

sources += gnome.compile_resources(
  'gtd-plugin-resources',
  join_paths(plugins_dir, 'plugins.gresource.xml'),
    source_dir: [ plugins_dir, join_paths(meson.build_root(), 'plugins') ],
        c_name: 'todo_plugins',
  dependencies: plugins_confs,
        export: true,
)

sources += gnome.compile_resources(
  'gtd-icon-resources',
  join_paths(icons_dir, 'icons.gresource.xml'),
    source_dir: [ icons_dir ],
        c_name: 'todo_icons',
        export: true,
)

enum = 'gtd-enum-types'

sources += gnome.mkenums(
        enum,
     sources: enum_headers,
  c_template: enum + '.c.template',
  h_template: enum + '.h.template'
)

incs = [
  top_inc,
  include_directories(
    'engine',
    'provider',
    'logging',
    'task-list-view',
    'notification',
    'interfaces',
    'widgets',
    'sidebar',
  )
]

cflags = [
  '-DPACKAGE_DATA_DIR="@0@"'.format(gnome_todo_pkgdatadir),
  '-DPACKAGE_LIB_DIR="@0@"'.format(gnome_todo_pkglibdir),
  '-DPACKAGE_LOCALE_DIR="@0@"'.format(gnome_todo_localedir),
  '-DPACKAGE_SRC_DIR="@0@"'.format(meson.current_source_dir()),
  '-DUI_DATA_DIR="@0@"'.format(join_paths(gnome_todo_pkgdatadir, 'style'))
]

ldflags = [ '-Wl,--export-dynamic' ]


#########
# Debug #
#########

debug_conf = configuration_data()
debug_conf.set('BUGREPORT_URL', 'https://gitlab.gnome.org/GNOME/gnome-todo/issues/new')
debug_conf.set10('ENABLE_TRACING', gnome_todo_tracing)


debug = 'gtd-debug.h'

sources += configure_file(
          input: debug + '.in',
         output: debug,
  configuration: debug_conf,
)


##############
# gnome-todo #
##############

gnome_todo = executable(
  meson.project_name(),
               sources,
  include_directories: incs,
         dependencies: [ vcs_identifier_h, gtd_deps ],
               c_args: cflags,
            link_args: ldflags,
              install: true,
          install_dir: gnome_todo_bindir
)


###################
# Private library #
###################

libgtd = shared_library(
                'gtd',
              sources: sources,
              version: libversion,
            soversion: soversion,
  include_directories: incs,
         dependencies: gtd_deps,
               c_args: cflags
)

libgtd_dep = declare_dependency(
            link_with: libgtd,
  include_directories: src_inc,
         dependencies: gtd_deps
)


##############
# pkg-config #
##############

pkg.generate(
    libraries: libgtd,
      version: gnome_todo_version,
         name: 'GNOME To Do',
  description: 'Header and path for GNOME Todo Plugins',
     filebase: meson.project_name(),
      subdirs: meson.project_name(),
    variables: 'exec_prefix=' + gnome_todo_libexecdir,
  install_dir: join_paths(gnome_todo_libdir, 'pkgconfig')
)


#########################
# GObject-Introspection #
#########################

if get_option('introspection')
  gir_sources = files(
    'engine/gtd-manager.c',
    'engine/gtd-manager.h',
    'interfaces/gtd-activatable.c',
    'interfaces/gtd-activatable.h',
    'interfaces/gtd-panel.c',
    'interfaces/gtd-panel.h',
    'interfaces/gtd-provider.c',
    'interfaces/gtd-provider.h',
    'models/gtd-list-model-filter.c',
    'models/gtd-list-model-filter.h',
    'models/gtd-list-store.c',
    'models/gtd-list-store.h',
    'notification/gtd-notification.c',
    'notification/gtd-notification.h',
    'task-list-view/gtd-task-list-view.c',
    'task-list-view/gtd-task-list-view.h',
    'gtd-enums.h',
    'gtd-clock.c',
    'gtd-clock.h',
    'gtd-object.c',
    'gtd-object.h',
    'gtd-task.c',
    'gtd-task.h',
    'gtd-task-list.c',
    'gtd-task-list.h',
    'gtd-types.h',
    'gtd-window.c',
    'gtd-window.h'
  )

  gir_incs = [
    'Gio-2.0',
    'GObject-2.0',
    'Gtk-3.0'
  ]

  gir_extra_args = '--warn-all'

  gir_dir = join_paths(gnome_todo_datadir, '@0@-@1@'.format('gir', gnome_todo_gir_version))
  typelib_dir = join_paths(gnome_todo_libdir, '@0@-@1@'.format('girepository', gnome_todo_gir_version))

  gnome.generate_gir(
                 libgtd,
                sources: gir_sources,
              namespace: gnome_todo_gir_namespace,
              nsversion: gnome_todo_gir_version,
      identifier_prefix: gnome_todo_gir_namespace,
          symbol_prefix: gnome_todo_gir_namespace.to_lower(),
               includes: gir_incs,
    include_directories: incs,
             extra_args: gir_extra_args,
                install: true,
        install_dir_gir: gir_dir,
    install_dir_typelib: typelib_dir,
  )
endif

apps += Atomic::App
app_headers += apps/atomic/app.h

apps_src += $(addprefix apps/atomic/,\
  app.cpp \
	table_controller.cpp \
	atomic_cell.cpp \
	atom_info.cpp \
)

i18n_files += $(call i18n_without_universal_for,atomic/base) $(call i18n_without_universal_for,atomic/atomsName)

$(eval $(call depends_on_image,apps/atomic/app.cpp,apps/atomic/atomic_icon.png))
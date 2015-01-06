###############################################################################
############################ COMMON MODULES ###################################
###############################################################################


###############################################################################
#
# New Module Step 5.
#       MODULENAME                := yes
###############################################################################

ifeq ($(ALL_MODULES),yes)
        CHEMICAL_REACTIONS        := yes
        CONTACT                   := yes
        FLUID_MASS_ENERGY_BALANCE := yes
        HEAT_CONDUCTION           := yes
        LINEAR_ELASTICITY         := yes
        MISC                      := yes
        NAVIER_STOKES             := yes
        PHASE_FIELD               := yes
        RICHARDS                  := yes
        SOLID_MECHANICS           := yes
        TENSOR_MECHANICS          := yes
        WATER_STEAM_EOS           := yes
endif

ifeq ($(PHASE_FIELD),yes)
        TENSOR_MECHANICS          := yes
endif

###############################################################################
########################## MODULE REGISTRATION ################################
###############################################################################
#
# New Module Step 6.
#
# ifeq ($(MODULENAME),yes)
# APPLICATION_DIR    := $(MOOSE_DIR)/modules/modulename
# APPLICATION_NAME   := modulename
# include $(FRAMEWORK_DIR)/app.mk
# libmesh_CXXFLAGS   += -DMODULENAME
# endif
#
###############################################################################

ifeq ($(CHEMICAL_REACTIONS),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/chemical_reactions
  APPLICATION_NAME   := chemical_reactions
  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(CONTACT),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/contact
  APPLICATION_NAME   := contact
  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(FLUID_MASS_ENERGY_BALANCE),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/fluid_mass_energy_balance
  APPLICATION_NAME   := fluid_mass_energy_balance
  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(HEAT_CONDUCTION),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/heat_conduction
  APPLICATION_NAME   := heat_conduction
  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(LINEAR_ELASTICITY),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/linear_elasticity
  APPLICATION_NAME   := linear_elasticity
  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(MISC),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/misc
  APPLICATION_NAME   := misc
  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(NAVIER_STOKES),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/navier_stokes
  APPLICATION_NAME   := navier_stokes
  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(TENSOR_MECHANICS),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/tensor_mechanics
  APPLICATION_NAME   := tensor_mechanics
  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(PHASE_FIELD),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/phase_field
  APPLICATION_NAME   := phase_field

  # Dependency on tensor mechanics
  DEPEND_MODULES     := tensor_mechanics

  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(RICHARDS),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/richards
  APPLICATION_NAME   := richards
  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(SOLID_MECHANICS),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/solid_mechanics
  APPLICATION_NAME   := solid_mechanics
  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(WATER_STEAM_EOS),yes)
  APPLICATION_DIR    := $(MOOSE_DIR)/modules/water_steam_eos
  APPLICATION_NAME   := water_steam_eos
  include $(FRAMEWORK_DIR)/app.mk
endif

ifeq ($(ALL_MODULES),yes)
  ifneq ($(INCLUDE_COMBINED),no)
    APPLICATION_DIR    := $(MOOSE_DIR)/modules/combined
    APPLICATION_NAME   := combined
    include $(FRAMEWORK_DIR)/app.mk
  endif
endif

PRODUCT_NAME := tunl
PRODUCT := lib$(PRODUCT_NAME).a

DEBUG_PRODUCT_NAME := $(PRODUCT_NAME)-debug
DEBUG_PRODUCT := lib$(DEBUG_PRODUCT_NAME).a

WIN_PRODUCT_NAME := $(PRODUCT_NAME)-win
WIN_PRODUCT := lib$(WIN_PRODUCT_NAME).a

WIN_DEBUG_PRODUCT_NAME := $(PRODUCT_NAME)-debug-win
WIN_DEBUG_PRODUCT := lib$(WIN_DEBUG_PRODUCT_NAME).a

TESTS := run-tunl-tests
DEBUG_TESTS := $(TESTS)-debug
WIN_TESTS := $(TESTS)-win
WIN_DEBUG_TESTS := $(TESTS)-debug-win

MAINDIR := ${CURDIR}
BINDIR  := $(MAINDIR)/bin

INCDIR  := $(MAINDIR)/includes
INCDIR_EXT := $(MAINDIR)/external_includes

SRCDIR  := $(MAINDIR)/src
SRCDIR_EXT := $(MAINDIR)/external_src
SRCDIR_TESTS := $(MAINDIR)/tests

LIBDIR	:= $(MAINDIR)/libs
OBJDIR  := $(MAINDIR)/obj
RELEASE_OBJDIR := $(OBJDIR)/release/
DEBUG_OBJDIR := $(OBJDIR)/debug/
DEPDIR := $(OBJDIR)/dep/
WIN_RELEASE_OBJDIR := $(OBJDIR)/win-release/
WIN_DEBUG_OBJDIR := $(OBJDIR)/win-debug/

MKDIR_P := mkdir -p
RM_RF := rm -rf
ALL := /*

# Language --------------------------------------------------------------------
EXTENSION := cpp
LANGUAGE_STANDARD := -std=c++11
COMPILER := g++
LINKER := g++
WIN_COMPILER := x86_64-w64-mingw32-g++
WIN_LINKER := x86_64-w64-mingw32-g++

# Flags -----------------------------------------------------------------------
# ----- General ---------------------------------------------------------------
INCLUDES := -I $(INCDIR) -I $(INCDIR_EXT)
SYS_LIBRARIES :=
WIN_LIBRARIES :=
LINUX_LIBRARIES :=
LIBRARIES := -L$(LIBDIR) $(SYS_LIBRARIES)
WARNING_FLAGS := -Wall -Wextra
DEPENDENCY_GENERATION_FLAGS := -MMD -MP

# ----- Release ---------------------------------------------------------------
UNUSED_CODE_COMPILER_FLAGS := #-ffunction-sections -fdata-sections -flto
OPTIMIZATION_LEVEL := -O3
RELEASE_FLAGS := $(OPTIMIZATION_LEVEL) $(UNUSED_CODE_COMPILER_FLAGS)
RELEASE_LINKER_FLAGS := #-Wl,--gc-sections
RELEASE_MACROS :=

# ----- Debug -----------------------------------------------------------------
DEBUG_FLAGS := -O0 -g
DEBUG_MACROS :=






# -----------------------------------------------------------------------------
# DON'T MESS WITH ANYTHING AFTER THIS UNLESS YOU KNOW WHAT YOU'RE DOING -------
# -----------------------------------------------------------------------------

GENERAL_COMPILER_FLAGS := $(LANGUAGE_STANDARD) $(WARNING_FLAGS) $(DEPENDENCY_GENERATION_FLAGS)

LINKER_FLAGS := $(RELEASE_LINKER_FLAGS)
COMPILER_FLAGS := $(RELEASE_FLAGS) $(GENERAL_COMPILER_FLAGS) $(RELEASE_MACROS)

# -----------------------------------------------------------------------------
# Getting all the source files ------------------------------------------------
# -----------------------------------------------------------------------------

# Finds all .$(EXTENSION) files and puts them into SRC
SRC := $(wildcard $(SRCDIR)/*.$(EXTENSION))
SRC_EXT := $(wildcard $(SRCDIR_EXT)/*/*.$(EXTENSION))
SRC_TESTS := $(wildcard $(SRCDIR_TESTS)/*.$(EXTENSION))

# -----------------------------------------------------------------------------
# Generating all the relevant object files ------------------------------------
# -----------------------------------------------------------------------------

# Creates .o files for every .$(EXTENSION) file in SRC (patsubst is pattern substitution)
RELEASE_OBJ     := $(patsubst $(SRCDIR)/%.$(EXTENSION),$(RELEASE_OBJDIR)/%.o,$(SRC))
DEBUG_OBJ       := $(patsubst $(SRCDIR)/%.$(EXTENSION),$(DEBUG_OBJDIR)/%.o,$(SRC))
WIN_RELEASE_OBJ := $(patsubst $(SRCDIR)/%.$(EXTENSION),$(WIN_RELEASE_OBJDIR)/%.o,$(SRC))
WIN_DEBUG_OBJ   := $(patsubst $(SRCDIR)/%.$(EXTENSION),$(WIN_DEBUG_OBJDIR)/%.o,$(SRC))

RELEASE_OBJ     += $(patsubst $(SRCDIR_EXT)/%.$(EXTENSION),$(RELEASE_OBJDIR)/%.o,$(SRC_EXT))
DEBUG_OBJ       += $(patsubst $(SRCDIR_EXT)/%.$(EXTENSION),$(DEBUG_OBJDIR)/%.o,$(SRC_EXT))
WIN_RELEASE_OBJ += $(patsubst $(SRCDIR_EXT)/%.$(EXTENSION),$(WIN_RELEASE_OBJDIR)/%.o,$(SRC_EXT))
WIN_DEBUG_OBJ   += $(patsubst $(SRCDIR_EXT)/%.$(EXTENSION),$(WIN_DEBUG_OBJDIR)/%.o,$(SRC_EXT))

RELEASE_TEST_OBJ     := $(patsubst $(SRCDIR_TESTS)/%.$(EXTENSION),$(RELEASE_OBJDIR)/tests/%.o,$(SRC_TESTS))
DEBUG_TEST_OBJ       := $(patsubst $(SRCDIR_TESTS)/%.$(EXTENSION),$(DEBUG_OBJDIR)/tests/%.o,$(SRC_TESTS))
WIN_RELEASE_TEST_OBJ := $(patsubst $(SRCDIR_TESTS)/%.$(EXTENSION),$(WIN_RELEASE_OBJDIR)/tests/%.o,$(SRC_TESTS))
WIN_DEBUG_TEST_OBJ   := $(patsubst $(SRCDIR_TESTS)/%.$(EXTENSION),$(WIN_DEBUG_OBJDIR)/tests/%.o,$(SRC_TESTS))

# -----------------------------------------------------------------------------
# Creates .d files (dependencies) for every .$(EXTENSION) file in SRC ---------
# -----------------------------------------------------------------------------

DEP := $(patsubst $(SRCDIR)/%.$(EXTENSION),$(DEPDIR)/%.d,$(SRC)) $(patsubst $(SRCDIR)/%.$(EXTENSION),$(DEPDIR)/%.d,$(SRC))
# Finds all lib*.a files and puts them into LIB
# LIB := $(wildcard $(LIBDIR)/lib*.a)

# -----------------------------------------------------------------------------
# Generate all the target files -----------------------------------------------
# -----------------------------------------------------------------------------

# $^ is list of dependencies and $@ is the target file
$(LIBDIR)/$(PRODUCT): directories $(RELEASE_OBJ)
	ar rcs $@ $(RELEASE_OBJ)

$(LIBDIR)/$(DEBUG_PRODUCT): directories $(DEBUG_OBJ)
	ar rcs $@ $(DEBUG_OBJ)

$(LIBDIR)/$(WIN_DEBUG_PRODUCT): directories $(WIN_DEBUG_OBJ)
	ar rcs $@ $(WIN_DEBUG_OBJ)

$(LIBDIR)/$(WIN_PRODUCT): directories $(WIN_RELEASE_OBJ)
	ar rcs $@ $(WIN_RELEASE_OBJ)

# Compile tests
$(BINDIR)/$(TESTS): directories $(RELEASE_TEST_OBJ) $(LIBDIR)/$(PRODUCT) $(LIB)
	$(LINKER) $(LINKER_FLAGS) $(COMPILER_FLAGS) $(RELEASE_TEST_OBJ) -l$(PRODUCT_NAME) $(LIBRARIES) $(LINUX_LIBRARIES) -o $@

$(BINDIR)/$(DEBUG_TESTS): directories $(DEBUG_TEST_OBJ) $(LIBDIR)/$(DEBUG_PRODUCT) $(LIB)
	$(LINKER) $(LINKER_FLAGS) $(COMPILER_FLAGS) $(DEBUG_TEST_OBJ) -l$(DEBUG_PRODUCT_NAME) $(LIBRARIES) $(LINUX_LIBRARIES) -o $@

$(BINDIR)/$(WIN_DEBUG_TESTS): directories $(WIN_DEBUG_TEST_OBJ) $(LIBDIR)/$(WIN_DEBUG_PRODUCT) $(LIB)
	$(WIN_LINKER) $(LINKER_FLAGS) $(COMPILER_FLAGS) $(WIN_DEBUG_TEST_OBJ) -l$(WIN_DEBUG_PRODUCT_NAME) -L/usr/x86_64-w64-mingw32/lib/ $(LIBRARIES) $(WIN_LIBRARIES) -o $@

$(BINDIR)/$(WIN_TESTS): directories $(WIN_RELEASE_TEST_OBJ) $(LIBDIR)/$(WIN_PRODUCT) $(LIB)
	$(WIN_LINKER) $(LINKER_FLAGS) $(COMPILER_FLAGS) $(WIN_RELEASE_TEST_OBJ) -l$(WIN_PRODUCT_NAME) -L/usr/x86_64-w64-mingw32/lib/ $(LIBRARIES) $(WIN_LIBRARIES) -o $@

# -----------------------------------------------------------------------------
# Generate all the object files -----------------------------------------------
# -----------------------------------------------------------------------------

# Compile individual .$(EXTENSION) source files into object files
$(RELEASE_OBJDIR)/%.o: $(SRCDIR)/%.$(EXTENSION)
	$(COMPILER) $(COMPILER_FLAGS) -MF $(DEPDIR)/$*.d $(INCLUDES) -c $< -o $@

$(DEBUG_OBJDIR)/%.o: $(SRCDIR)/%.$(EXTENSION)
	$(COMPILER) $(COMPILER_FLAGS) -MF $(DEPDIR)/%.d $(INCLUDES) -c $< -o $@

$(WIN_RELEASE_OBJDIR)/%.o: $(SRCDIR)/%.$(EXTENSION)
	$(WIN_COMPILER) $(COMPILER_FLAGS) -MF $(DEPDIR)/$*.d $(INCLUDES) -c $< -o $@

$(WIN_DEBUG_OBJDIR)/%.o: $(SRCDIR)/%.$(EXTENSION)
	$(WIN_COMPILER) $(COMPILER_FLAGS) -MF $(DEPDIR)/$*.d $(INCLUDES) -c $< -o $@

# Compile all the test object files
$(RELEASE_OBJDIR)/tests/%.o: $(SRCDIR_TESTS)/%.$(EXTENSION)
	$(COMPILER) $(COMPILER_FLAGS) -MF $(DEPDIR)/$*.d $(INCLUDES) -c $< -o $@

$(DEBUG_OBJDIR)/tests/%.o: $(SRCDIR_TESTS)/%.$(EXTENSION)
	$(COMPILER) $(COMPILER_FLAGS) -MF $(DEPDIR)/%.d $(INCLUDES) -c $< -o $@

$(WIN_RELEASE_OBJDIR)/tests/%.o: $(SRCDIR_TESTS)/%.$(EXTENSION)
	$(WIN_COMPILER) $(COMPILER_FLAGS) -MF $(DEPDIR)/$*.d $(INCLUDES) -c $< -o $@

$(WIN_DEBUG_OBJDIR)/tests/%.o: $(SRCDIR)/%.$(EXTENSION)
	$(WIN_COMPILER) $(COMPILER_FLAGS) -MF $(DEPDIR)/$*.d $(INCLUDES) -c $< -o $@

-include $(DEP)

.PHONY: directories

directories: $(OBJDIR) $(RELEASE_OBJDIR) $(DEBUG_OBJDIR) $(WIN_RELEASE_OBJDIR) $(WIN_DEBUG_OBJDIR) $(DEPDIR)
$(OBJDIR):
	$(MKDIR_P) $(OBJDIR)

$(RELEASE_OBJDIR):
	$(MKDIR_P) $(RELEASE_OBJDIR)/tests

$(DEBUG_OBJDIR):
	$(MKDIR_P) $(DEBUG_OBJDIR)/tests

$(WIN_RELEASE_OBJDIR):
	$(MKDIR_P) $(WIN_RELEASE_OBJDIR)/tests

$(WIN_DEBUG_OBJDIR):
	$(MKDIR_P) $(WIN_DEBUG_OBJDIR)/tests

$(DEPDIR):
	$(MKDIR_P) $(DEPDIR)

.PHONY: test

test: $(BINDIR)/$(TESTS)

.PHONY: test-debug

test-debug: $(BINDIR)/$(DEBUG_TESTS)

.PHONY: win-test

win-test: $(BINDIR)/$(WIN_TESTS)

.PHONY: win-test-debug

win-test-debug: $(BINDIR)/$(WIN_DEBUG_TESTS)

.PHONY: clean

clean:
	$(RM_RF) $(OBJDIR)$(ALL) $(BINDIR)/$(PRODUCT) $(BINDIR)/$(DEBUG_PRODUCT) $(BINDIR)/$(WIN_PRODUCT) $(BINDIR)/$(WIN_DEBUG_PRODUCT)

.PHONY: release

test release: COMPILER_FLAGS := $(RELEASE_FLAGS) $(GENERAL_COMPILER_FLAGS)
test release: LINKER_FLAGS := $(RELEASE_LINKER_FLAGS)
test release: directories $(RELEASE_OBJ) $(LIBDIR)/$(PRODUCT)

.PHONY: debug

test-debug debug: COMPILER_FLAGS := $(DEBUG_FLAGS) $(GENERAL_COMPILER_FLAGS)
test-debug debug: LINKER_FLAGS :=
test-debug debug: directories $(DEBUG_OBJ) $(LIBDIR)/$(DEBUG_PRODUCT)

.PHONY: win-release

win-test win-release: COMPILER_FLAGS := $(RELEASE_FLAGS) $(GENERAL_COMPILER_FLAGS)
win-test win-release: LINKER_FLAGS := $(RELEASE_LINKER_FLAGS)
win-test win-release: directories $(WIN_RELEASE_OBJ) $(LIBDIR)/$(WIN_PRODUCT)

.PHONY: win-debug

win-test-debug win-debug: COMPILER_FLAGS := $(DEBUG_FLAGS) $(GENERAL_COMPILER_FLAGS)
win-test-debug win-debug: LINKER_FLAGS :=
win-test-debug win-debug: directories $(WIN_DEBUG_OBJ) $(LIBDIR)/$(WIN_DEBUG_PRODUCT)

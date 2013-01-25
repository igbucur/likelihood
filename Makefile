ROOT_DIR = /home/x11bucur/likelihood
SRC_DIR = $(ROOT_DIR)/src
OBJ_DIR = $(ROOT_DIR)/build
BIN_DIR = $(ROOT_DIR)/bin

RC := root-config
INC_DIR := $(shell $(RC) --incdir)
LIB_DIR := $(shell $(RC) --libdir)
MATHLIBS = -lRooFitCore -lRooFit -lRooStats -lHistFactory


#------------------------------------------------------------------------------

ifeq ($(shell $(RC) --has-roofit),yes)

CPP_FILES := $(wildcard $(SRC_DIR)/*.cxx)
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(notdir $(basename $(CPP_FILES)))))

endif

LIBS := -lCore -lRIO
CXXFLAGS = -g --std=c++11 -fopenmp
LDFLAGS = -fopenmp


#----------------------------------------------------------------------------

OBJS = $(TESTOBJ) $(TEST2OBJ) $(ADDOBJ) $(MODELOBJ) $(PVALUEOBJ) $(COMBINEDOBJ) $(TFNOBJ)
TESTS = $(TEST) $(TEST2)

$(TEST):	$(TESTOBJ)
	$(LD) $(LDFLAGS) $^ $(LIB_DIR) $(LIBS) $(OutPutOpt)$@
	@echo "$@ done"




#----------------------------------------------------------------------------

all: ll

$(OBJ_FILES): $(CPP_FILES)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c -o $@ $<

ll: $(OBJ_FILES)
	$(CXX) $(LDFLAGS) -L$(LIB_DIR) $(LIBS) $^ -o $(BIN_DIR)/$@

print:
	@echo "$(CPP_FILES)"
	@echo "$(OBJ_FILES)"   

clean:
	@rm -f $(OBJ_FILES)

again: clean ll

.SUFFIXES: .$(SrcSuf)

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<



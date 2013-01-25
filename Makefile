ROOT_DIR = /home/x11bucur/likelihood
SRC_DIR = $(ROOT_DIR)/src
OBJ_DIR = $(ROOT_DIR)/build
BIN_DIR = $(ROOT_DIR)/bin

RC := root-config
INC_BOOST = ~/boost_1_52_0
LIB_BOOST = ~/boost_1_52_0/stage/lib
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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -I$(INC_BOOST) -c -o $@ $<

ll: $(OBJ_FILES)
	$(CXX) $(LDFLAGS) -L$(LIB_DIR) -L$(LIB_BOOST) $(LIBS) $^ -o $(BIN_DIR)/$@

print:
	@echo "$(CPP_FILES)"
	@echo "$(OBJ_FILES)"   

clean:
	@rm -f $(OBJ_FILES)

again: clean ll

.SUFFIXES: .$(SrcSuf)

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<



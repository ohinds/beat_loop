.DELETE_ON_ERROR:

.SUFFIXES:
.SUFFIXES:  .o .cpp

# suffix rule for subsidiary source files
# (see http://www.gnu.org/manual/make/html_chapter/make_10.html#SEC111)
$(OBJ_DIR)/%.o: %.cpp %.h
	@$(ECHO) '[make: building $@]'
	$(CC) $(C_FLAGS) -o $@ -c $<

HDR_FILES = $(wildcard *.h)
SRC_FILES = $(wildcard ./*.cpp)
TMP_FILES = $(patsubst ./%,$(OBJ_DIR)/%,$(SRC_FILES))
OBJ_FILES = $(TMP_FILES:.cpp=.o)

beat_loop: $(OBJ_FILES)
	$(CC) -o $(BIN_DIR)/beat_loop $(OBJ_FILES) $(C_LIBS)

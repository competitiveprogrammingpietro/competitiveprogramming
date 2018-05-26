CXX_FLAGS = -std=c++11 -Wall  -g 

% : %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $? $(PIETRO) -DDEBUG

clean:
	rm tree_and_queries

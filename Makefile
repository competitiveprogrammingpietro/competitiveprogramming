CXX_FLAGS = -std=c++11 -Wall -g 

% : %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $?


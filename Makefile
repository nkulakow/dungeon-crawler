CXX = clang++
CXX_CPP_FLAGS = -c -Wall
CXX_SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
REMOVE = rm -rf
OBJECTS = main.o Game.o Character.o Enemy.o Skeleton.o Skull_Boss.o Map.o Chamber.o Corridor.o Party.o Menu.o Hero.o Wizard.o Warrior.o Fight.o Game_Over.o Victory.o


all: app remove_o

app: $(OBJECTS)
	$(CXX) $(OBJECTS) -o app $(CXX_SFML_FLAGS)

main.o: main.cpp
	$(CXX) $(CXX_CPP_FLAGS) main.cpp

Game.o: src/Logic/Game.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Logic/Game.cpp

Character.o: src/Characters/Character.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Characters/Character.cpp

Enemy.o: src/Characters/Enemies/Enemy.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Characters/Enemies/Enemy.cpp

Skeleton.o: src/Characters/Enemies/Skeleton.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Characters/Enemies/Skeleton.cpp

Skull_Boss.o: src/Characters/Enemies/Skull_Boss.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Characters/Enemies/Skull_Boss.cpp

Map.o: src/Map/Map.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Map/Map.cpp

Chamber.o: src/Map/Chamber.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Map/Chamber.cpp

Corridor.o: src/Map/Corridor.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Map/Corridor.cpp

Room.o: src/Map/Room.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Map/Room.cpp

Party.o: src/Logic/Party.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Logic/Party.cpp

Menu.o: src/Menu/Menu.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Menu/Menu.cpp

Game_Over.o: src/Menu/Game_Over.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Menu/Game_Over.cpp

Victory.o: src/Menu/Victory.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Menu/Victory.cpp

Hero.o: src/Characters/Heros/Hero.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Characters/Heros/Hero.cpp

Wizard.o: src/Characters/Heros/Wizard.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Characters/Heros/Wizard.cpp

Warrior.o: src/Characters/Heros/Warrior.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Characters/Heros/Warrior.cpp

Fight.o: src/Logic/Fight.cpp
	$(CXX) $(CXX_CPP_FLAGS) src/Logic/Fight.cpp


remove_o:
	$(REMOVE) *.o

clean:
	$(REMOVE) app


test: test_out remove_test_o

test_out: tests/test_all.o
	$(CXX) tests/test_all.o -o test $(CXX_SFML_FLAGS)

test_all.o: tests/test_all.cpp
	$(CXX) $(CXX_CPP_FLAGS) tests/test_all.cpp

remove_test_o:
	$(REMOVE) tests/test_all.o

clean_test:
	$(REMOVE) test
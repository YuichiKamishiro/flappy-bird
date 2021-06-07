all:
		g++ -ISFML/include/ -IBox2d/include/ -LSFML/lib/ -LBox2d/lib/ src/Main.cpp src/App.cpp src/Bird.cpp src/Listener.cpp src/Ground.cpp src/Pillar.cpp src/Counter.cpp -lsfml-graphics -lsfml-system -lsfml-window -lbox2d -o build -w

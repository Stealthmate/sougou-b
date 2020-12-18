MT_FILES=mt.h mt.c

LIBRARY_SOURCES=Simulation.cpp Strategy.cpp RandomStrategy.cpp Metrics.cpp SlotMachine.cpp EpsilonGreedyStrategy.cpp SoftmaxStrategy.cpp
%.o: %.cpp %.hpp
	g++ $<

mt: ${MT_FILES} mt_main.c
	gcc -o mt $^


k1: k1.cpp ${LIBRARY_SOURCES} ${MT_FILES}
	g++ -o k1 $^

k2: k2.cpp ${LIBRARY_SOURCES} ${MT_FILES}
	g++ -o k2 $^

k3: k3.cpp ${LIBRARY_SOURCES} ${MT_FILES}
	g++ -o k3 $^

k%_data.csv: k%
	./k$* > $@

k1_plots: k1_data.csv
	gnuplot k1_plot.p
k2_plots: k2_data.csv
	gnuplot k2_plot.p
k3_plots: k3_data.csv
	gnuplot k3_plot.p


clean:
	rm -f *.o
	rm -f mt
	rm -f k1

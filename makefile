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

data/:
	mkdir -p data

data/k%_data.csv: k% data/
	./k$* > $@

plots/:
	mkdir -p plots

plots/k%_engaged_machines.png: data/k%_data.csv plot_engaged_machines.p plots/
	gnuplot -e "outputfile='$@'" -e "inputfile='$<'" plot_engaged_machines.p
plots/k%_avg_reward.png: data/k%_data.csv plot_avg_reward.p plots/
	gnuplot -e "outputfile='$@'" -e "inputfile='$<'" plot_avg_reward.p
plots/k%_cdr.png: data/k%_data.csv plot_cdr.p plots/
	gnuplot -e "outputfile='$@'" -e "inputfile='$<'" plot_cdr.p

plot_k1: plots/k1_engaged_machines.png plots/k1_avg_reward.png plots/k1_cdr.png

clean:
	rm -f *.o
	rm -f mt
	rm -f k1 k2 k3
	rm -rf data
	rm -rf plots

# Do not delete intermediates
.SECONDARY:

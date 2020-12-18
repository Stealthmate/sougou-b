MT_FILES=$(addprefix src/,mt.h mt.c)
LIBRARY_SOURCES=$(addprefix src/,Simulation.cpp Strategy.cpp RandomStrategy.cpp Metrics.cpp SlotMachine.cpp EpsilonGreedyStrategy.cpp SoftmaxStrategy.cpp UCBStrategy.cpp Kadai.cpp)

%.o: %.cpp %.hpp
	g++ $<

bin/mt: $(MT_FILES) mt_main.c
	mkdir -p bin
	gcc -o $@ $^

bin/k%: src/k%.cpp $(LIBRARY_SOURCES) $(MT_FILES)
	mkdir -p bin
	g++ -o $@ $^

data/%.csv: bin/%
	mkdir -p data
	$< > $@

plots/%/engaged_machines.png: data/%.csv gnuplot/plot_engaged_machines.p
	mkdir -p plots/$*
	gnuplot -e "outputfile='$@'" -e "inputfile='$<'" gnuplot/plot_engaged_machines.p
plots/%/avg_reward.png: data/%.csv gnuplot/plot_avg_reward.p
	mkdir -p plots/$*
	gnuplot -e "outputfile='$@'" -e "inputfile='$<'" gnuplot/plot_avg_reward.p
plots/%/cdr.png: data/%.csv gnuplot/plot_cdr.p
	mkdir -p plots/$*
	gnuplot -e "outputfile='$@'" -e "inputfile='$<'" gnuplot/plot_cdr.p
plots/%/mu.png: data/%.csv gnuplot/plot_mu.p
	mkdir -p plots/$*
	gnuplot -e "outputfile='$@'" -e "inputfile='$<'" gnuplot/plot_mu.p
plots/%/rho.png: data/%.csv gnuplot/plot_rho.p
	mkdir -p plots/$*
	gnuplot -e "outputfile='$@'" -e "inputfile='$<'" gnuplot/plot_rho.p
plots/%/F.png: data/%.csv gnuplot/plot_F.p
	mkdir -p plots/$*
	gnuplot -e "outputfile='$@'" -e "inputfile='$<'" gnuplot/plot_F.p


plot_k1 plot_k2 plot_k3 plot_k4: plot_%: $(addprefix plots/%/,engaged_machines.png avg_reward.png cdr.png)
plot_k2: plots/k2/mu.png
plot_k3: plots/k3/rho.png
plot_k4: plots/k4/F.png

clean:
	rm -f *.o
	rm -f mt
	rm -f k1 k2 k3 k4
	rm -rf data
	rm -rf plots

# Do not delete intermediates
.SECONDARY:

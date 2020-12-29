MT_FILES=$(addprefix src/,mt.h mt.c)
LIBRARY_SOURCES=$(addprefix src/,Simulation.cpp Strategy.cpp RandomStrategy.cpp Metrics.cpp SlotMachine.cpp EpsilonGreedyStrategy.cpp SoftmaxStrategy.cpp UCBStrategy.cpp Kadai.cpp Experiment.cpp)

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

data/k5-eg.csv: bin/k5
	bin/k5
data/k5-sm.csv: bin/k5
	bin/k5
data/k5-ucb.csv: bin/k5
	bin/k5
data/k5-stats-eg.csv: bin/k5
	bin/k5
data/k5-stats-sm.csv: bin/k5
	bin/k5
data/k5-stats-ucb.csv: bin/k5
	bin/k5

data/k6-stats-1.csv: bin/k6
	bin/k6
data/k6-stats-2.csv: bin/k6
	bin/k6
data/k6-stats-3.csv: bin/k6
	bin/k6

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

plots/k5/eg_%.png: gnuplot/plot_%.p data/k5-eg.csv
	mkdir -p plots/k5
	gnuplot -e "outputfile='$@'" -e "inputfile='data/k5-eg.csv'" -e "parameter='Epsilon'" $<

plots/k5/sm_%.png: gnuplot/plot_%.p data/k5-sm.csv
	mkdir -p plots/k5
	gnuplot -e "outputfile='$@'" -e "inputfile='data/k5-sm.csv'" -e "parameter='Tau'" $<

plots/k5/ucb_%.png: gnuplot/plot_%.p data/k5-ucb.csv
	mkdir -p plots/k5
	gnuplot -e "outputfile='$@'" -e "inputfile='data/k5-ucb.csv'" -e "parameter='Alpha'" $<

plot_k1 plot_k2 plot_k3 plot_k4: plot_%: $(addprefix plots/%/,engaged_machines.png avg_reward.png cdr.png)
plot_k2: plots/k2/mu.png
plot_k3: plots/k3/rho.png
plot_k4: plots/k4/F.png
plot_k5: plots/k5/eg_param_avg_reward.png plots/k5/eg_param_cdr.png plots/k5/sm_param_avg_reward.png plots/k5/sm_param_cdr.png plots/k5/ucb_param_avg_reward.png plots/k5/ucb_param_cdr.png plots/k5-stats-eg/avg_reward.png plots/k5-stats-eg/cdr.png plots/k5-stats-sm/avg_reward.png plots/k5-stats-sm/cdr.png plots/k5-stats-ucb/avg_reward.png plots/k5-stats-ucb/cdr.png
plot_k6: plots/k6-stats-1/avg_reward.png plots/k6-stats-1/cdr.png plots/k6-stats-2/avg_reward.png plots/k6-stats-2/cdr.png plots/k6-stats-3/avg_reward.png plots/k6-stats-3/cdr.png

clean:
	rm -f *.o
	rm -f mt
	rm -f k1 k2 k3 k4
	rm -rf data
	rm -rf plots

# Do not delete intermediates
.SECONDARY:

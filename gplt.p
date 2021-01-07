set xlabel "Time (min)" offset 0,0.7;
set xrange [0 to ax]
set style line 1 lt 1 lw 1.5 lc rgb "#3465a4"
set style line 2 lt 1 lw 1.5 lc rgb "#f57900"
set style line 3 lt 1 dt 2 lw 3.0 lc rgb "#4e9a06"
eflow=2; sqo=eflow+1; fsc2=sqo+1; qsc2=fsc2+1; fsq1=qsc2+1; fum=fsq1+1; bypas=fum+1; qh=bypas+1; psi=qh+1; fc1=psi+1; rosc2=fc1+1; rosc3=rosc2+1; fc2=rosc3+1; ca=fc2+1;
Glu_m=ca+1; OAAm=Glu_m+1; psio=OAAm+1; Na_i=psio+1; OAAc=Na_i+1; Glu_o=OAAc+1; Glu_i=Glu_o+1; ATP=Glu_i+1;
#//plot '011110rbm' u ($1):($2) every 3::3::293 ps 0.25 lc rgb "#3465a4" not;
set xtics 1.0 nomirror;
set ytics nomirror;
set border 3;
set key vert at graph 0.5,0.7 left Right samplen 1;

#set t pngcairo enhanced dashed font "arial,10" size 700,2.5*68;
#set output fno;
#set multiplot layout 1,3;
#set label 1 "A" at graph 0.1,1.0 font "arial,12"
#set ytics 0.02
#set ylabel "FMN SQ in CI " offset 2;
#plot fn1 using ($1):fsq1 w l ls 1 not, fn2 using ($1):fsq1 w l ls 2 not
#set label 1 "B"
#set yrange [-0.045 to *]
#set ytics 0.1
#set ylabel "FAD SQ in CII " offset 2;
#plot fn1 using ($1):fsc2 w l ls 1 t"ROS", fn2 using ($1):fsc2 w l ls 2 t"work";
#set label 1 "C"
#set ytics 0.2
#set ylabel "SQ at Qo in CIII " offset 2;
#plot fn1 using ($1):sqo w l ls 1 not, fn2 using ($1):sqo w l ls 2 not;
#--------------------------------------------------------------

set t pngcairo enhanced dashed font "arial,10" size 500,5*68;
set output fno;
set multiplot layout 2,2;
set label 1 "A" at graph 0.1,1.0 font "arial,12"
set ylabel "ΔΨ (mV)" offset 2;
set yrange [-5.0 to *]
plot fn1 using ($1):psi w l ls 1 not, fn2 using ($1):psi w l ls 2 not;

set label 1 "B"
set ylabel "VO_2 (nmol/mg/min)" offset 1.5;
plot fn1 using ($1):eflow w l ls 1 t"ROS", fn2 using ($1):eflow w l ls 2 t"work";

set label 1 "C" at graph 0.2,1.0
set ylabel "QH_2 " offset 2;
set ytics 0.2
set yrange [-0.05 to *]
plot fn1 using ($1):qh w l ls 1 not, fn2 using ($1):qh w l ls 2 not;

set label 1 "D" at graph 0.1,1.0
set ylabel "ATP" offset 2;
plot fn1 using ($1):ATP w l ls 1 not, fn2 using ($1):ATP w l ls 2 not;

#set yrange [-0.0 to *]
#set label 1 "A" at graph 0.05,1.0 font "arial,12"
#set ylabel "ROS in CII, nmol/mg" offset 1;
#plot fn1 using ($1):rosc2 w l ls 2 not#"work"# fn2 using ($1):rosc2 w l ls 3 t"glu", "rot1" using ($1):rosc2 w l ls 1 t"GLU", fn1 using ($1):rosc2 w l ls 2 t"work";
#set ylabel "ROS in CI" offset 2;
#plot fn1 using ($1):fc1 w l ls 2 not#, fn2 using ($1):Glu_i w l ls 3 not, "rot1" using ($1):Glu_i w l ls 1 not;
#set label 1 "D" 
#set ylabel "Glu mito (mM)" offset 2;
#plot fn1 using ($1):Glu_m w l ls 2 not#, fn2 using ($1):Glu_m w l ls 3 not, "rot1" using ($1):Glu_m w l ls 1 not;
#set ylabel "OAA mito (mM)" offset 2;
#plot fn1 using ($1):OAAm w l ls 2 not#, fn2 using ($1):OAAm w l ls 3 not, "rot1" using ($1):OAAm w l ls 1 not;
#set ylabel "qsc2" offset 2;
#plot fn1 using ($1):qsc2 w l ls 1 not, fn2 using ($1):qsc2 w l ls 2 not;
unset multiplot



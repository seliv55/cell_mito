#set size 0.65,0.65;
set t pngcairo enhanced dashed font "arial,10" size 600,61.8*3;
#set t svg enhanced dashed font "arial,10" size 600,61.8*3;
set output "cont.png";
set multiplot layout 1,2
set style line 1 lt 1 lw 1.5 lc rgb "#3465a4"
set style line 2 lt 1 lw 1.5 lc rgb "#f57900"
set xlabel "max ATPase, arbitrary units" offset 0,0.7;
fac=0.0002;
set xrange [0.:*]
set yrange [-0.1:*]
set xtics nomirror;
set ytics nomirror;
set border 3;
eflow=3; sqo=eflow+1; fsc2=sqo+1; qsc2=fsc2+1; fsq1=qsc2+1; fum=fsq1+1; bypas=fum+1; qh=bypas+1; psi=qh+1; fc1=psi+1; rosc2=fc1+1; rosc3=rosc2+1; fc2=rosc3+1;
ca=fc2+1;
Glu_m=ca+1; OAAm=Glu_m+1; psio=OAAm+1; Na_i=psio+1; OAAc=Na_i+1; Glu_o=OAAc+1; Glu_i=Glu_o+1; ATP=Glu_i+1;
#set ylabel "ROS in C3, nM" offset 2;
#plot '00000' using ($1/fac):rosc3 w l ls 2 not;
set ytics 0.2;
set label 1 "A" at graph 0.05,1.0 font "arial,12"
set ylabel "SQ at Qo in CIII (relative)" offset 2;
plot '00000' using ($1/fac):sqo w l ls 2 not, 'a00000' using ($1/fac):sqo w l ls 1 not
#set yrange [-3:*]
#set ytics 20;
#set label 1 "B"
#set ylabel "Ψ(mV)" offset 2;
#plot '00000' using ($1/fac):psi w l ls 2 not, 'a00000' using ($1/fac):psi w l ls 1 not;
#set ylabel "ROS in C2, nM" offset 2;
#plot '00000' using ($1/fac):rosc2 w l ls 2 not;
#set yrange [-0.1:*]
#set ytics 0.2;
#set label 1 "C"
#set ylabel "ATP, mM" offset 2;
#plot '00000' using ($1/fac):ATP w l ls 2 not, 'a00000' using ($1/fac):ATP w l ls 1 not
set yrange [-11:*]
set ytics 100;
set label 1 "B"
#set label 1 "D"
set ylabel "VO_2 (nmol/mg/min)" offset 2;
plot '00000' using ($1/fac):eflow w l ls 2 not, 'a00000' using ($1/fac):eflow w l ls 1 not;


import os

for x in range(0,19):
    os.system("sed 's:_xstart_:%d:g' <_template_comparison.C >A.C" %(x*52+1))
    os.system("sed 's:_xend_:%d:g' <A.C >B.C" %((x+1)*52+1))
    os.system("sed 's:_tower_number_:%s:' <B.C >D.C" %(x+1))
    os.system("sed 's:_plotname_:tower_%s_comparison:' <D.C >comparison_by_tower/tower_%s_comparison.C" %((x+1),(x+1)))

    os.system("rm A.C B.C D.C")

    os.system("root -b -q comparison_by_tower/tower_%s_comparison.C" %(x+1))



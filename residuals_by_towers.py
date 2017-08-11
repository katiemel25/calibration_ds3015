import os

for x in range(0,19):
    os.system("sed 's:_xstart_:%d:g' <_template_residuals.C >first_tower_test_a.C" %(x*52+1))
    os.system("sed 's:_xend_:%d:g' <first_tower_test_a.C>first_tower_test_b.C" %((x+1)*52+1))
    os.system("sed 's:tower_number:%s:' <first_tower_test_b.C>first_tower_test_c.C" %(x+1))
    os.system("sed 's:_plotname_:tower_%s_residuals:' <first_tower_test_c.C >residuals_by_tower/tower_%s_residuals.C" %((x+1),(x+1)))

    os.system("rm first_tower_test_a.C first_tower_test_b.C first_tower_test_c.C")

    os.system("root -b -q residuals_by_tower/tower_%s_residuals.C" %(x+1))


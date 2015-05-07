# StatsForAgeC
apply anthropometric data to all ages

A generic c++ library to calculate anthropometric (weight, length/height, head circumference, body mass index) statistics (centiles, z scores) for age, taking into account gestational age at birth up to 2 years. usually data is available to about 24 weeks corrected gestation. statistics are linear interpolated - i.e. if the child is 2years, 2months and 15 days, the average is obtained between 2y2m and 2y3m.

A library and te ado file are include for use as a stata plugin

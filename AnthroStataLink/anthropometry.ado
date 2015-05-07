program anthropometry
version 12.1

syntax newvarname(generate) [if] [in], Value(varname numeric) Agedays(varname numeric) Male(varname numeric) [Gestationweeksatbirth(varname numeric) Length Weight Headcircumference BMI]
//double weightInKg, double daysOfAge, bool isMale, double totalWeeksGestAtBirth=TermGestation and returning returnVar
if (c(os)!="Windows") {
	di err "Not currently configured to work outside windows environment - please contact the author if you would like this ported to your platform" _newline as txt "Alternatively the open source c++ code is available on github if you have the software, skills and would like to compile it yourself"
	error 9999
}
/*
if (c(bit)==32) {
	capture program anthrostatalink, plugin using("AnthroStataLink.dll")
}
else {
	capture program anthrostatalink, plugin using("StataAnthroLink_x64.dll")
}

if (_rc!=0 & _rc!=110) {
	error _rc
}
*/

qui count `if' `in'
if (r(N) == 0) {
	error 2000
}

local measure `length' `weight' `headcircumference' `bmi'
local optcount:word count `measure'
if (`optcount'==0){
	local measure weight
}
if (`optcount' >1) {
	di as error "only ONE of Length, Weight, Headcircumference or BMI may be specified"
	error 184
}

if ("`gestationweeksatbirth'" == "") {
	tempvar gestationweeksatbirth
	qui gen double `gestationweeksatbirth'=40
}

plugin call anthrostatalink `value' `agedays' `male' `gestationweeksatbirth' `varlist' `if' `in', `measure'

end

program anthrostatalink, plugin using("StatsForAgeC.dll")

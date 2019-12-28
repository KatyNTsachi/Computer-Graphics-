INSTRUCTIONS:

* fix the lights: light calculation is implemented in getColorAt which calls 
  getFlatColorAt, getGouraudColorAt, getPhongColorAt.
. getFlatColorAt is already implemented but it dosn't work well, I think it is because
  of the summetion. I think it is a good idea to actually implement the summetion
  and then see what happpens. I think that the sudden change in color in the middle is
  because the dot produt becomes negative and the collors are interpreted as unsigned.
* implement getGouraudColorAt and getPhongColorAt

* we need to normalize the light for all of the image

TASKS
		
	NEW HW
	remove tranformLine from scene
QUESTIONS

BUGS:


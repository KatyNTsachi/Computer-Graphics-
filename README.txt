INSTRUCTIONS:
 * reset your local branch to commit NEW HW and then pull the changes from the remote
   repository. this is nessessery because I force pushed some commits. use git to look
   at the changes instead of reading the entire code.
* fix the lights: light calculation is implemented in getColorAt which calls 
  getFlatColorAt, getGouraudColorAt, getPhongColorAt.
. getFlatColorAt is already implemented but it dosn't work well, I think it is because
  of the summetion. I think it is a good idea to actually implement the summetion
  and then see what happpens. I think that the sudden change in color in the middle is
  because the dot produt becomes negative and the collors are interpreted as unsigned.
* implement getGouraudColorAt and getPhongColorAt



TASKS
		
	NEW HW
	
QUESTIONS

BUGS:


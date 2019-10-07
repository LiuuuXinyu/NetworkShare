Dim newdir
Set newdir = wscript.createobject("scripting.filesystemobject")
For k=1 to 10
anewfolder="c:\chapter" & k
        newdir.createfolder(anewfolder)
next

# create folder for exercices files and move into them

$path = "D:\Coding_WorkPlace\L2_Info4A\Partie_G\Exercices\"
$name = "XG0"; 

cd $path;
1..6 | ForEach {
MD "$name$_";
Move-Item -Path ".\$name$_.cpp" -Destination ".\$name$_\$name$_.cpp";
}
# powerhshell script to create main folder

$main_folder_name = @("A","B","C","D","E","F","G","H","I");
$path = "D:\Coding_WorkPlace\L2_Info4A\"; 

cd $path;
$main_folder_name.foreach{
    MD "Partie_$PSItem";
}


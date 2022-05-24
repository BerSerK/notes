```
# 管理员权限运行cmd
wsl --shutdown
diskpart
# open window Diskpart
select vdisk file="C:\Users\yeshi\AppData\Local\Packages\CanonicalGroupLimited.Ubuntu20.04onWindows_79rhkp1fndgsc\LocalState\ext4.vhdx"
attach vdisk readonly
compact vdisk
detach vdisk
exit
```

make fclean
git add -A
echo "\x1b[32;01m[\x1b[31;01mOK\x1b[32;01m]\x1b[30;01m - \x1b[33;01mADDED EVERYTHING\x1b[0m"
git commit -m "$1"
echo "\x1b[32;01m[\x1b[31;01mOK\x1b[32;01m]\x1b[30;01m - \x1b[33;01mCOMMITED \x1b[36;01m\"$1\"\x1b[0m"
git push
echo "\x1b[32;01m[\x1b[31;01mOK\x1b[32;01m]\x1b[30;01m - \x1b[33;01mPUSHED\x1b[0m"

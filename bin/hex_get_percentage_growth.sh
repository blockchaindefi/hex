#!/bin/bash -ue

# Total and locked save file
file_total_supply="$HOME/.hex_total_supply"
file_locked_supply="$HOME/.hex_locked_supply"


function error_end()
{
  echo "ERROR: $@" >&2
  exit 1
}

for fils_in_path in hex_percentage_growth wget stat
do
  which $fils_in_path  >/dev/null || error_end "Missing command: $fils_in_path"
done


# Save total and locked supply so as not to overload the server
if [ ! -s "$file_total_supply" ] || [ "$(( $(date +"%s") - $(stat -c "%Y" $file_total_supply) ))" -gt "$((60*60*2))" ]; then
  echo "Update supply  $file_total_supply  AND  $file_locked_supply files"
  wget -q --timeout=8 --output-document=$file_total_supply  https://hexvisionpublicapi.azurewebsites.net/api/TotalSupply
  wget -q --timeout=8 --output-document=$file_locked_supply https://hexvisionpublicapi.azurewebsites.net/api/LockedSupply
  if [ ! -s "$file_total_supply" ] || [ ! -s "$file_locked_supply" ]; then
    rm -f "$file_total_supply"
    error_end "Can't download total or locked supply data..?"
  fi
fi

TotalSupply="$(cat  $file_total_supply)"
LockedSupply="$(cat $file_locked_supply)"

hex_percentage_growth -t $TotalSupply -l $LockedSupply $*


<img width="1330" alt="Capture d’écran 2024-06-04 à 23 47 05" src="https://github.com/axel-lukongo/ft_malloc/assets/88286839/c94ae8f3-db2f-46fb-aef4-c9fca7241eec">
the pointers _tail always point to the last vm_page of the zone, that mean every time we want to add a new page, we gone add it in _tail->next

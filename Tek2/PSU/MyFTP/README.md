# MyFTP

## Utilisation (necessite deux terminaux):
### Premier terminal: serveur
```
$ make
$ ./server 2000 `pwd`
```
### Second terminal: client
```
$ nc 127.0.0.1 2000
$ USER Anonymous
$ PASS
```

### Note obtenue: 19
### Philippe De Sousa, PSO 2021.

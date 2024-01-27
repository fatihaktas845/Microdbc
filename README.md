![logo](image.png)

### Kurulum
  * Kurulum çok basit! Sadece proje içerisindeki başlık dosyasını ve kaynak kod dosyasını projenize dahil etmeniz gerekmektedir.
  * Ayrıca derleyici bağımlılıklarını da eklemeyi unutmayın. Örneğin Visual Studio'da `odbc32.lib` ve `msvcrxxx.lib` bağımlılıkları eklenirken MinGW C++ Compiler'da `-lodbc32` ve `-lodbc` bağımlılıklarını eklemelisiniz.

### Gereksinimler
  * Microsoft ODBC Server for SQL 17.0 veya üzeri

### ÖNEMLİ!!!
  * `msvcrxxx.lib` bağımlılığındaki `xxx` derleyicinin CRT sürümünü belirtmektedir. Örneğin:
     * Visual Studio 2019 için: `msvcr140.lib`
     * Visual Studio 2017 için: `msvcr140.lib`
    ## NOT:
       * Visual Studio derleyicinizin CRT sürümünü derleyicinizin dokümanlarında veya proje ayarlarında bulabilirsiniz.

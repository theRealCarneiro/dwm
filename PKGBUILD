pkgname=dwm
pkgver=6.2
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
depends=('libx11' 'libxinerama')
makedepends=('git' 'make')
optdepends=('polybar-dwm-module: polybar with dwm module')
#source=('dwm::git://github.com/theRealCarneiro/dwm.git')
md5sums=('SKIP')

build() {
	cd $pkgname
	make
}

package() {
	cd $pkgname
	make clean PREFIX=/usr DESTDIR=$pkgdir install
}

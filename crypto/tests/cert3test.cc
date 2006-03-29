#include "wvx509.h"
#include "wvrsa.h"
#include "wvcrash.h"
#include <assert.h>

    const WvString strrsa = "3082025e02010002818100b507269be849a872"
"3ec72d6f769c9a4e228f3a4e7c4c948776d8f525364b98ced92031592a054042f5"
"fe63757cc270ac2a71785347d6d784f4b871161e13e3ac2abe5c1830d8d2401a72"
"976435fd4170c72aa063eedb45fa04d7ced92974162363d78715fb044d66e6ee38"
"2a2f1ea70e8d8c50b9a2a575ab14cd7d5646604635020301000102818100b277a4"
"469c10d1f21f95f963240a6bcd9020a818ec4e0b3829a0e6bd92f3a0687c825264"
"571aea29999efbaabe1e6b3a3075c16c492cb338ae928f5a80b897005fdeca7966"
"14f58329552bfd117755fae42ba39aa3266bb2560377d5d747e31ddfd2ae1bbd9b"
"8979e8748d4d47573588a4140715fbc14ea373f2461517749641024100f0b0ddee"
"376d6e08c9dc0bce540e9b464bf23121241cf6dd69fd67c9e195c6dce0ddb47012"
"56761567a8c70fff3e12cc412e8cb74f120eb620d7d129624c359d024100c08acd"
"153fe5f801c81a85a62b63f50b9346ebe350a18c3aecd11379a17093f52fdea874"
"df97b22189dd4ca479723422c0a5b5124873e087f316cbf681d2fb79024100810c"
"33517fc25a56b7f4151861151bc78afca5bec1200e741459db85f03f5fca197e85"
"39f97b0600dffd2c0db5aa5065d724e02980698c1db66a4028d21d4e3902405e57"
"a48574f9c9bb95c0e91bb2c7179ac45f4bd5e5fc4229dd3fd4bb144f852fee74bb"
"360918db3f73bdeb7febc1f9a9cd9b644dc112864216ea64a634969c81024100e5"
"453ec9a3cdbe2fe17e86b32e998fe8713066ed254a60390f7898e4e536dea92af7"
"743d55a35fad75c14fe1e239251c471e133ca8e85ef3a1d3c5b6b288bfda";

    const WvString strcert = "3082030030820269a003020102020460ad1ad"
"5300d06092a864886f70d010105050030818e310b3009060355040613024341310"
"f300d060355040813065175656265633111300f060355040713084d6f6e7472656"
"16c31123010060355040a13095465737479204f6e65311d301b060355040313146"
"1726961322e7765617665726e65742e6e756c6c31283026060a0992268993f22c6"
"4011916187765626d6173746572407765617665726e65742e6e756c6c301e170d3"
"034303333313230343235315a170d3134303332393230343235315a30818e310b3"
"009060355040613024341310f300d060355040813065175656265633111300f060"
"355040713084d6f6e747265616c31123010060355040a13095465737479204f6e6"
"5311d301b0603550403131461726961322e7765617665726e65742e6e756c6c312"
"83026060a0992268993f22c64011916187765626d6173746572407765617665726"
"e65742e6e756c6c30819f300d06092a864886f70d010101050003818d003081890"
"2818100b507269be849a8723ec72d6f769c9a4e228f3a4e7c4c948776d8f525364"
"b98ced92031592a054042f5fe63757cc270ac2a71785347d6d784f4b871161e13e"
"3ac2abe5c1830d8d2401a72976435fd4170c72aa063eedb45fa04d7ced92974162"
"363d78715fb044d66e6ee382a2f1ea70e8d8c50b9a2a575ab14cd7d56466046350"
"203010001a3693067301106096086480186f842010104040302064030230609608"
"6480186f842010c0416161461726961322e7765617665726e65742e6e756c6c300"
"e0603551d0f0101ff0404030202a4301d0603551d250416301406082b060105050"
"7030106082b06010505070302300d06092a864886f70d010105050003818100b2b"
"fe7b80feec0bfe23250f5d9eb3d409364628c001fee50185eb755ffb863093fe23"
"973c939fdd03bc90b32eb697f1eb9b4a7a0134ee78a509992da0d803af22b5148a"
"76b197a54126be4a3d03897ed6cc98e77e65b797aee3f3b66c17afb4a2fd6dc498"
"cd86f4d7952cfde7d1e044a38373f80b9d1da51461267a83d967f24";

const WvString dName1("/CN=test.foo.com/DC=foo/DC=com");

int main(int argc, char **argv)
{
    wvcrash_setup(argv[0]);
    WvX509Mgr cacert(strcert, strrsa);
    
    WvX509Mgr clicert(dName1, 1024);
    WvString certreq(clicert.certreq());

    fprintf(stderr, "Request:\n%s", certreq.cstr());

    WvString signedcert(cacert.signreq(certreq));

    fprintf(stderr, "Cert:\n%s", signedcert.cstr());

    clicert.decode(WvX509Mgr::CertPEM, signedcert);

    fprintf(stderr, "Issuer:%s\n", clicert.get_issuer().cstr());
    
    bool foo = clicert.validate(&cacert);

    fprintf(stderr, foo ? "Passed\n" : "Failed\n");

    return 0;
}

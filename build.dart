import 'package:anbuild/anbuild.dart';

void main(args, port) {
  runBuildMain(args, port, () {
    var result = new TargetResult();
    result.addIncludes('c++', ['include']);
    result.addScanSources(['src']);
    port.send(result.pack());
  });
}

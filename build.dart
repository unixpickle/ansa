import 'package:anbuild/anbuild.dart';

void main(_, port) {
  var result = new TargetResult();
  result.addIncludes('c++', ['include']);
  result.addScanSources(['src']);
  port.send(result.pack());
}

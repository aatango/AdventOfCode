gtest = dependency('gtest', main: true, required: true, version: '>=1.14.0')
gmock = dependency('gmock', required: true, version: '>=1.14.0')

testSources = [
  'HistorianHysteriaTests.cc',
  'RedNosedReportsTests.cc',
  'MullItOverTests.cc',
  'CeresSearchTests.cc',
  'PrintQueueTests.cc',
  'BridgeRepairTests.cc',
  'ResonantCollinearityTests.cc',
]

exe = executable(
  'AdventOfCode2024Tests',
  testSources,
  implicit_include_directories: false,
  include_directories: '../Sources',
  link_with: AdventOfCode2024,
  dependencies: [gtest, gmock]
)

test('AdventOfCode 2024 Tests', exe, protocol: 'gtest')

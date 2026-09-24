import unittest,sys
sys.path.insert(0,'simulation')
from efuse_sim import EFuse
class TestEFuse(unittest.TestCase):
 def test_normal(self): e=EFuse();e.enable();e.sample(4);self.assertEqual(e.state,'ON')
 def test_oc(self): e=EFuse();e.enable();[e.sample(9,10) for _ in range(4)];self.assertEqual(e.state,'ON');e.sample(9,20);self.assertEqual(e.fault,'OVERCURRENT')
 def test_short(self): e=EFuse();e.enable();e.sample(20,1);self.assertEqual(e.fault,'SHORT_CIRCUIT')
 def test_reset(self): e=EFuse();e.enable();e.sample(20);e.reset();self.assertEqual(e.fault,'NONE')
if __name__=='__main__':unittest.main()

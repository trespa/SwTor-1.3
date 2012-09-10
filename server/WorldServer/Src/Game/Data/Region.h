#pragma once

#include <vector>
#include <cstdint>

namespace Swtor
{
	namespace Game
	{
		static const uint64_t AlderaanS = 4611686023868513034LLU;
		static const uint64_t BalmorraI = 4611686022220993772LLU;
		static const uint64_t BalmorraR = 4611686040187270001LLU;
		static const uint64_t BelsavisS = 4611686025952170568LLU;
		static const uint64_t CoruscantR = 4611686019047870293LLU;
		static const uint64_t DromundKaasI = 4611686019618382666LLU;
		static const uint64_t FlashPointTransitionRegionalImperial = 4611686027378771320LLU;
		static const uint64_t FlashPointTransitionRegionalRepublic = 4611686033507370314LLU;
		static const uint64_t HothS = 4611686025038950088LLU;
		static const uint64_t HuttaI = 4611686019802841877LLU;
		static const uint64_t IlumS = 4611686039258170278LLU;
		static const uint64_t KorribanI = 4611686022825732973LLU;
		static const uint64_t NarShaddaaS = 4611686027681070173LLU;
		static const uint64_t OrdMantellR = 4611686019802843831LLU;

		static const uint64_t PCShip_DefenderConsular = 4611686051284471420LLU;
		static const uint64_t PCShip_DefenderKnight = 4611686051284476033LLU;
		static const uint64_t PCShip_FuryWarrior = 4611686051284477081LLU;
		static const uint64_t PCShip_FuryInquisitor = 4611686051284477465LLU;
		static const uint64_t PCShip_MantisD5 = 4611686051849071023LLU;
		static const uint64_t PCShip_PhantomX70B = 4611686051849071159LLU;
		static const uint64_t PCShip_ThunderclapBT7 = 4611686053134031672LLU;
		static const uint64_t PCShip_XSFreighter = 4611686053487831502LLU;

		static const uint64_t QueshS = 4611686030163371363LLU;
		static const uint64_t TarisI = 4611686070551329793LLU;
		static const uint64_t TarisR = 4611686023014030644LLU;
		static const uint64_t TatooineS = 4611686018427650020LLU;
		static const uint64_t TythonR = 4611686019869492753LLU;
		static const uint64_t VossS = 4611686025383332936LLU;

		/**
		 * Region class
		 */
		class Region
		{
		public:

			Region();

			virtual ~Region();

		private:
		};
	}
}
#include <Logic/Session.h>
#include <Logic/World.h>
#include <DAO/Account.h>
#include <Crypt/RSA.h>
#include <System/Tools.h>

namespace Swtor
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::SendIntroduceConnection()
		{
			Network::Packet packet(Opcode::SMSG_SIGNATURE_RESPONSE, 0xFFFF, 0xFFFF, 0x00);
			packet << (uint32_t)0x0000C4AB << "u1832" << "userentrypoint6" << "9cf74d45:1a6cc459:6fa57dc2";
			packet << (uint64_t)0x0 << "" << "" << (uint64_t)0x0;

			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::SendClientInformation()
		{
			Network::Packet packet(Opcode::SMSG_CLIENT_INFORMATION, 0xC4AB, 0x0000, 0x00);

			std::ostringstream os;
			os << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
			os << "<client title=\"Test Client\" useSyncClock=\"true\" loglevel=\"debug\" repositoryserver=\"RepositoryServer:repositoryserver\" worldserver=\"WorldServer:worldserver\" trackingserver=\"TrackingServer:trackingserver\" gamesystemsserver=\"GameSystemsServer:gamesystemsserver\" serverscriptcompiler=\"ScriptCompilerServer:scriptcompiler\" clientscriptcompiler=\"ScriptCompilerClient:scriptcompiler\" searchserver=\"SearchServer:searchserver\" chatgateway=\"ChatGateway:chatgateway\" mailserver=\"Mail:mailserver\" auctionserver=\"AuctionServer:auctionserver\" universeID=\"he1012\" networkNapTimeMS=\"20\" worldServiceDirectoryConfigs=\"CacheFilePath=HeroEngineCache\\Dev;cmdScriptActivity=;gameName=Dev;\" baseServiceDirectoryConfigs=\"ClientCachePath=REPLACEWITHLOCALAPPDATAPATH\\HeroEngine\\REPLACEWITHUNIVERSEID;cmdScriptActivity=;DynamicDetailAltPathName=search all Repository;DynamicDetailAltTexturePath=/;DynamicDetailTexturePath=/art;HeightMapBillbaordAltPathName=search all Repository;HeightMapBillboardAltPath=/;HeightmapBillboardPath=/art;HeightmapTerrainMeshAltPath=/;HeightmapTerrainMeshAltPathName=search all Repository;HeightmapTerrainMeshPath=/art;HeightmapTextureAltPath=/;HeightmapTextureAltPathName=search all Repository;HeightmapTexturePath=/art;HeroEngineScriptWarning=This script is part of HeroEngine and should not be modified for game specific purposes.;KNOWN_ISSUES_URL=;STATUS_HOST=bwa-dev-uvs02;STATUS_SERVER_PORT=61111;VERSION_NOTES_URL=;ArtDirectory=\\mmo1\\;SplashLogoPath=/bwa_splash.png;ShaderPath=/art/shaders;\" clientCachePath=\"REPLACEWITHLOCALAPPDATAPATH\\HeroEngine\\REPLACEWITHUNIVERSEID\" additionalClientConfigs=\"WorldName=he1012;SHARD_PUBLIC_NAME=he1012;CacheFilePath=HeroEngineCache\\Dev;cmdScriptActivity=&apos;&apos;;gameName=Dev;DynamicDetailAltPathName=&apos;search all Repository&apos;;DynamicDetailAltTexturePath=/;DynamicDetailTexturePath=/art;HeightMapBillbaordAltPathName=&apos;search all Repository&apos;;HeightMapBillboardAltPath=/;HeightmapBillboardPath=/art;HeightmapTerrainMeshAltPath=/;HeightmapTerrainMeshAltPathName=&apos;search all Repository&apos;;HeightmapTerrainMeshPath=/art;HeightmapTextureAltPath=/;HeightmapTextureAltPathName=&apos;search all Repository&apos;;HeightmapTexturePath=/art;HeroEngineScriptWarning=&apos;This script is part of HeroEngine and should not be modified for game specific purposes.&apos;;KNOWN_ISSUES_URL=&apos;&apos;;STATUS_HOST=bwa-dev-uvs02;STATUS_SERVER_PORT=61111;VERSION_NOTES_URL=&apos;&apos;;ArtDirectory=\\mmo1\\;SplashLogoPath=/bwa_splash.png;ShaderPath=/art/shaders;ScreencatcherURL=127.0.0.1;AssetTimestamp=AssetTimestamp;eGCSS_URL=emulatornexus.com:443\">";
			os << "<gamesystemsservers first=\"GameSystemsServer:gamesystemsserver\"/><biomon metricspublisherserver=\"biomonserver:biomon\">";
			os << "<biomon-sampler service_family=\"he1012\" service_type=\"gameclient\">";
			os << "</biomon-sampler></biomon><access-rights>";
			os << "<client name=\"Automaton.exe\">";
			os << "<network name=\"BWA\" address=\"10.2.0.0/15\"/><network name=\"AUS\" address=\"10.64.10.0/24\"/><network name=\"BWE\" address=\"10.0.0.0/15\"/><network name=\"Mythic\" address=\"10.18.11.0/24\"/></client><client name=\"HeroBlade.exe\">";
			os << "<network name=\"Ultizen\" address=\"172.16.0.0/24\"/><network name=\"CheQ\" address=\"172.16.1.0/24\"/><network name=\"SperaSoft\" address=\"172.16.2.0/24\"/><network name=\"SperaSoftQA\" address=\"172.16.4.0/24\"/><network name=\"Ringtail\" address=\"172.16.11.0/24\"/><network name=\"BWA\" address=\"10.2.0.0/15\"/><network name=\"BWE\" address=\"10.0.0.0/15\"/><network name=\"Tiburon\" address=\"10.8.0.0/16\"/><network name=\"IE\" address=\"10.148.3.0/24\"/><network name=\"EARS\" address=\"10.14.161.0/24\"/><network name=\"Mythic\" address=\"10.18.11.0/24\"/><network name=\"Globant\" address=\"172.16.6.0/24\"/><network name=\"EAMadrid\" address=\"10.20.136.0/24\"/><network name=\"AUS\" address=\"10.64.10.0/24\"/><network name=\"BWI\" address=\"10.22.128.0/17\"/></client></access-rights></client>";

			packet << (uint32_t)0x0 << os.str();

			mConnection->Write(packet);
		}
		//---------------------------------------------------------------------
	}
}
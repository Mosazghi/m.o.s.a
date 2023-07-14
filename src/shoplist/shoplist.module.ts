import { Module } from '@nestjs/common';
import { MongooseModule } from '@nestjs/mongoose';
import { UserModule } from 'src/user/user.module';
import { Shoplist, ShoplistSchema } from './schema/shoplist.schema';
import { ShoplistController } from './shoplist.controller';
import { ShoplistService } from './shoplist.service';
@Module({
  imports: [
    UserModule,
    MongooseModule.forFeature([
      { name: Shoplist.name, schema: ShoplistSchema },
    ]),
  ],
  controllers: [ShoplistController],
  providers: [ShoplistService],
})
export class ShoplistModule {}

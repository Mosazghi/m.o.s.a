import { Module } from '@nestjs/common';
import { MongooseModule } from '@nestjs/mongoose';
import { Shoplist, ShoplistSchema } from './schema/shoplist.schema';
import { ShoplistController } from './shoplist.controller';
import { ShoplistService } from './shoplist.service';

@Module({
  imports: [
    MongooseModule.forFeature([
      { name: Shoplist.name, schema: ShoplistSchema },
    ]),
  ],
  controllers: [ShoplistController],
  providers: [ShoplistService],
})
export class ShoplistModule {}
